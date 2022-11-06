#ifndef XMLANDCSVPARSER_XMLPARSER_H
#define XMLANDCSVPARSER_XMLPARSER_H

#include <string>
#include <set>
#include <map>
#include <iostream>
#include "Address.h"
#include <fstream>
#include <locale>

class XmlParser {
private:
    std::string filePath_;
    std::set<Address<std::wstring>> allRecords_;
    std::map<Address<std::wstring>, unsigned int> duplicateRecords_;
    std::map<std::wstring, std::array<unsigned int, 5>> countBuildingsForEachCity_;
public:
    XmlParser() = default;
    void Read(const std::string &filePath); // read xml file and fill
    const std::string &getFilePath() const { return filePath_; }
    std::string &getFilePath() { return filePath_; }
    void writeDuplicateRecords();
    void writeCountBuildingsForEachCity();
};

void XmlParser::Read(const std::string &filePath) {

    filePath_ = filePath;

    std::wstring line;
    std::wifstream inFile;
    inFile.open(filePath_);
    inFile.imbue(std::locale("ru_RU.UTF8"));

    if (inFile.is_open()) {
        while (!inFile.eof()) {
            std::getline(inFile, line);
            if (line.find(L"item") != std::wstring::npos) {
                std::wstring city, street, house, floor;

                auto position = line.find(L"city");
                position += 6;
                while (true) {
                    wchar_t s = line[position];
                    if (s == '"') break;
                    city += s;
                    position++;
                }

                position = line.find(L"street");
                position += 8;
                while (true) {
                    wchar_t s = line[position];
                    if (s == '"') break;
                    street += s;
                    position++;
                }

                position = line.find(L"house");
                position += 7;
                while (true) {
                    wchar_t s = line[position];
                    if (s == '"') break;
                    house += s;
                    position++;
                }

                position = line.find(L"floor");
                position += 7;
                while (true) {
                    wchar_t s = line[position];
                    if (s == '"') break;
                    floor += s;
                    position++;
                }

                Address address(city, street, house, floor); // std::move

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

        inFile.close();
    } else {
        std::cout << "Unable to open input file " << filePath_ << std::endl;
    }
}

void XmlParser::writeDuplicateRecords() {
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

void XmlParser::writeCountBuildingsForEachCity() {
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

#endif //XMLANDCSVPARSER_XMLPARSER_H
