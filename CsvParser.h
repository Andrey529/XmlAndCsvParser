#ifndef XMLANDCSVPARSER_CSVPARSER_H
#define XMLANDCSVPARSER_CSVPARSER_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include "Address.h"
#include <fstream>
#include <iostream>
#include "csv.hpp"

class CsvParser {
private:
    std::string filePath_;
    std::unordered_set<Address<std::string>, AddressHasher<std::string>> allRecords_;
    std::unordered_map<Address<std::string>, unsigned int, AddressHasher<std::string>> duplicateRecords_;
    std::unordered_map<std::string, std::array<unsigned int, 5>> countBuildingsForEachCity_;

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

        if (allRecords_.contains(address)) {
            auto iteratorToNewRecord = duplicateRecords_.find(address);
            if (iteratorToNewRecord == duplicateRecords_.end()) { // if this record is new in duplicate records
                duplicateRecords_.insert(std::pair(address, 1));
            } else { // increment the count of duplicate record
                iteratorToNewRecord->second++;
            }
        }
        else {
            allRecords_.insert(address);
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
            outFile << "\nDuplicate records:" << std::endl;
            for (const auto &[record, count]: duplicateRecords_) {
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
            outFile << "\nCount buildings for each city:" << std::endl;
            for (const auto &[city, building]: countBuildingsForEachCity_) {
                outFile << "In the city " << city << ":" << std::endl;
                for (int i = 0; i < 5; ++i) {
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
