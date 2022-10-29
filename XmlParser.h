#ifndef XMLANDCSVPARSER_XMLPARSER_H
#define XMLANDCSVPARSER_XMLPARSER_H

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include "Address.h"

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

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


    using namespace xercesc;

    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        std::cout << "Unable to initialize xml parser" << std::endl;
        std::cout << XMLString::transcode(toCatch.getMessage());
        // Do failure processing here
        return;
    }

    SAX2XMLReader *parser = XMLReaderFactory::createXMLReader();
    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

    auto* defaultHandler = new DefaultHandler();
    parser->setContentHandler(defaultHandler);
    parser->setErrorHandler(defaultHandler);

    try {
        parser->parse(filePath_.c_str());
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return;
    }
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return;
    }
    catch (...) {
        std::cout << "Unexpected Exception \n" ;
        return;
    }

    delete parser;
    delete defaultHandler;

    XMLPlatformUtils::Terminate();

//    boost::property_tree::ptree tree;
//    boost::property_tree::read_xml(filePath_, tree);


//    for (boost::property_tree::ptree::value_type &v : tree.get_child("root")) {
//        const boost::property_tree::ptree &attributes = v.second.get_child("<xmlattr>");
//        Address address(std::move(attributes.get<std::string>("city")),
//                        std::move(attributes.get<std::string>("street")),
//                        std::move(attributes.get<std::string>("house")),
//                        std::move(attributes.get<std::string>("floor"))
//                        );
//
//        unsigned long sizeBeforeInsertion = allRecords_.size();
//        allRecords_.insert(address);
//        if (sizeBeforeInsertion == allRecords_.size()) { // record is duplicate
//            auto iteratorToNewRecord = duplicateRecords_.find(address);
//            if (iteratorToNewRecord == duplicateRecords_.end()) { // if this record is new in duplicate records
//                duplicateRecords_.insert(std::pair(address, 1));
//            }
//            else { // increment the count of duplicate record
//                iteratorToNewRecord->second++;
//            }
//        }
//        else {
//            auto iteratorToCity = countBuildingsForEachCity_.find(address.city_);
//            if (iteratorToCity == countBuildingsForEachCity_.end()) { // if this city is new
//                std::array<unsigned int, 5> tmp = {0,0,0,0,0};
//                tmp[std::stoi(address.floor_) - 1] = 1;
//                countBuildingsForEachCity_.insert(std::pair(address.city_, tmp));
//            }
//            else {
//                iteratorToCity->second[std::stoi(address.floor_) - 1]++;
//            }
//        }
//    }

    std::cout << "In file " << filePath_ << " " << allRecords_.size() << " unique records." << std::endl;
}

void XmlParser::writeDuplicateRecords() {
    std::cout << "\nDuplicate records:" << std::endl;
    for (const auto& [record, count] : duplicateRecords_) {
        std::cout << "city = " << record.city_ << ", street = " << record.street_ << ", house = " << record.house_
            << ", floor = " << record.floor_ << " - occurs " << count << " times." << std::endl;
    }
}

void XmlParser::writeCountBuildingsForEachCity() {
    std::cout << "\nCount buildings for each city:" << std::endl;
    for (const auto& [city, building] : countBuildingsForEachCity_) {
        std::cout << "In the city " << city << ":" << std::endl;
        for (int i = 0; i < 5; ++i) {
            std::cout << "\t" << building[i] << " " << i+1 << " floor houses" << std::endl;
        }
    }
}

#endif //XMLANDCSVPARSER_XMLPARSER_H
