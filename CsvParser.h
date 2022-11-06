#ifndef XMLANDCSVPARSER_CSVPARSER_H
#define XMLANDCSVPARSER_CSVPARSER_H

#include <string>
#include <set>
#include <map>
#include "Address.h"
#include <fstream>
#include <iostream>
#include "csv.hpp"

class CsvParser {
private:
    std::string filePath_;
    std::set<Address<std::string>> allRecords_;
    std::map<Address<std::string>, unsigned int> duplicateRecords_;
    std::map<std::string, std::array<unsigned int, 5>> countBuildingsForEachCity_;
public:
    CsvParser() = default;
    void Read(const std::string &filePath); // read csv file and fill
    const std::string &getFilePath() const { return filePath_; }
    std::string &getFilePath() { return filePath_; }
    void writeDuplicateRecords();
    void writeCountBuildingsForEachCity();
};

void CsvParser::Read(const std::string &filePath) {
    filePath_ = filePath;


    csv::CSVReader reader(filePath_);
    for (csv::CSVRow &row : reader) {
        Address<std::string> address(row["city"].get<std::string>(), row["street"].get<std::string>(),
                        row["house"].get<std::string>(), row["floor"].get<std::string>());
//        std::cout << address.city_ << ' ' << address.street_ << ' ' << address.house_ << ' ' << address.floor_ << std::endl;

        unsigned long sizeBeforeInsertion = allRecords_.size();
        allRecords_.insert(address);
        if (sizeBeforeInsertion == allRecords_.size()) { // record is duplicate
            auto iteratorToNewRecord = duplicateRecords_.find(address);
            if (iteratorToNewRecord == duplicateRecords_.end()) { // if this record is new in duplicate records
                duplicateRecords_.insert(std::pair(address, 1));
            } else { // increment the count of duplicate record
                iteratorToNewRecord->second++;
            }
        } else {
            auto iteratorToCity = countBuildingsForEachCity_.find(address.city_);
            if (iteratorToCity == countBuildingsForEachCity_.end()) { // if this city is new
                std::array<unsigned int, 5> tmp = {0, 0, 0, 0, 0};
                tmp[std::stoi(address.floor_) - 1] = 1;
                countBuildingsForEachCity_.insert(std::pair(address.city_, tmp));
            } else {
                iteratorToCity->second[std::stoi(address.floor_) - 1]++;
            }
        }
    }
}

void CsvParser::writeDuplicateRecords() {
    if (!duplicateRecords_.empty()) {
        std::ofstream outFile("/home/andrey/Projects/XmlAndCsvParser/data/output.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile.imbue(std::locale("ru_RU.UTF-8"));
//            std::wcout.imbue(std::locale("ru_RU.UTF-8"));
//            std::wcout << "\nDuplicate records:" << std::endl;
            outFile << "\nDuplicate records:" << std::endl;
            for (const auto &[record, count]: duplicateRecords_) {
//                std::wcout << "city = " << record.city_ << ", street = " << record.street_ << ", house = " << record.house_
//                           << ", floor = " << record.floor_ << " - occurs " << count << " times." << std::endl;
                outFile << "city = " << record.city_ << ", street = " << record.street_ << ", house = " << record.house_
                        << ", floor = " << record.floor_ << " - occurs " << count << " times." << std::endl;
            }
            outFile.close();
        } else {
            std::wcout << "Unable to open output file" << std::endl;
        }
    }
}

void CsvParser::writeCountBuildingsForEachCity() {
    if (!countBuildingsForEachCity_.empty()) {
        std::ofstream outFile("/home/andrey/Projects/XmlAndCsvParser/data/output.txt", std::ios::app);
        if (outFile.is_open()) {
            outFile.imbue(std::locale("ru_RU.UTF-8"));
//            std::wcout.imbue(std::locale("ru_RU.UTF-8"));
//            std::wcout << "\nCount buildings for each city:" << std::endl;
            outFile << "\nCount buildings for each city:" << std::endl;
            for (const auto &[city, building]: countBuildingsForEachCity_) {
//                std::wcout << "In the city " << city << ":" << std::endl;
                outFile << "In the city " << city << ":" << std::endl;
                for (int i = 0; i < 5; ++i) {
//                    std::wcout << "\t" << building[i] << " " << i + 1 << " floor houses" << std::endl;
                    outFile << "\t" << building[i] << " " << i + 1 << " floor houses" << std::endl;
                }
            }
            outFile.close();
        } else {
            std::wcout << "Unable to open output file" << std::endl;
        }
    }
}

#endif //XMLANDCSVPARSER_CSVPARSER_H
