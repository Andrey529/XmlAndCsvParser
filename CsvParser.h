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
    std::set<Address> allRecords_;
    std::map<Address, unsigned int> duplicateRecords_;
    std::map<std::wstring, std::array<unsigned int, 5>> countBuildingsForEachCity_;
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
}

void CsvParser::writeDuplicateRecords() {
    if (!duplicateRecords_.empty()) {
        std::wofstream outFile("/home/andrey/Projects/XmlAndCsvParser/data/output.txt", std::ios::app);
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
        std::wofstream outFile("/home/andrey/Projects/XmlAndCsvParser/data/output.txt", std::ios::app);
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
