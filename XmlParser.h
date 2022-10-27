#ifndef XMLANDCSVPARSER_XMLPARSER_H
#define XMLANDCSVPARSER_XMLPARSER_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include "Address.h"

class XmlParser {
private:
    std::string filePath_;
    std::set<Address> allRecords_;
    std::map<Address, unsigned int> duplicateRecords_;
    std::map<std::string, std::array<unsigned int, 5>> countBuildingsForEachCity_;
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

    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(filePath_, tree);

    for (boost::property_tree::ptree::value_type &v : tree.get_child("root")) {
        const boost::property_tree::ptree &attributes = v.second.get_child("<xmlattr>");
        Address address(std::move(attributes.get<std::string>("city")),
                        std::move(attributes.get<std::string>("street")),
                        std::move(attributes.get<std::string>("house")),
                        std::move(attributes.get<std::string>("floor"))
                        );

        int sizeBeforeInsertion = allRecords_.size();
        allRecords_.insert(address);
        if (sizeBeforeInsertion == allRecords_.size()) { // record is duplicate
            auto iteratorToNewRecord = duplicateRecords_.find(address);
            if (iteratorToNewRecord == duplicateRecords_.end()) { // if this record is new in duplicate records
                duplicateRecords_.insert(std::pair(address, 1));
            }
            else { // increment the count of duplicate record
                iteratorToNewRecord->second++;
            }
        }
        else {
            auto iteratorToCity = countBuildingsForEachCity_.find(address.city_);
//            if ()
        }
    }

    std::cout << allRecords_.size();
}

void XmlParser::writeDuplicateRecords() {
    for (const auto& [record, count] : duplicateRecords_) {
        std::cout << "city = " << record.city_ << ", street = " << record.street_ << ", house = " << record.house_
            << ", floor = " << record.floor_ << " - occurs " << count << " times." << std::endl;
    }
}

void XmlParser::writeCountBuildingsForEachCity() {
    for (const auto& [city, building] : countBuildingsForEachCity_) {
        std::cout << "In the city " << city << ":" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "\t" << building[i] << " " << i+1 << " floor houses";
        }
    }
}

#endif //XMLANDCSVPARSER_XMLPARSER_H
