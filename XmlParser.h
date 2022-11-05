#ifndef XMLANDCSVPARSER_XMLPARSER_H
#define XMLANDCSVPARSER_XMLPARSER_H

//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include "Address.h"
#include <fstream>

//#include <xercesc/util/PlatformUtils.hpp>
//#include <xercesc/sax2/SAX2XMLReader.hpp>
//#include <xercesc/sax2/XMLReaderFactory.hpp>
//#include <xercesc/sax2/DefaultHandler.hpp>
//#include <xercesc/util/XMLString.hpp>

class XmlParser {
private:
    std::string filePath_;
    std::set<Address> allRecords_;
    std::map<Address, unsigned int> duplicateRecords_;
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

    setlocale(LC_ALL,"ru_RU.UTF-8");
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
                    }
                    else { // increment the count of duplicate record
                        iteratorToNewRecord->second++;
                    }
                }
                else {
                    auto iteratorToCity = countBuildingsForEachCity_.find(address.city_);
                    if (iteratorToCity == countBuildingsForEachCity_.end()) { // if this city is new
                        std::array<unsigned int, 5> tmp = {0,0,0,0,0};
                        tmp[std::stoi(address.floor_) - 1] = 1;
                        countBuildingsForEachCity_.insert(std::pair(address.city_, tmp));
                    }
                    else {
                        iteratorToCity->second[std::stoi(address.floor_) - 1]++;
                    }
                }
            }
        }

        inFile.close();
    }
    else {
        std::cout << "Unable to open file " << filePath_ << std::endl;
    }



//    using namespace xercesc;
//
//    try {
//        XMLPlatformUtils::Initialize();
//    }
//    catch (const XMLException& toCatch) {
//        std::cout << "Unable to initialize xml parser" << std::endl;
//        std::cout << XMLString::transcode(toCatch.getMessage());
//        // Do failure processing here
//        return;
//    }
//
//    SAX2XMLReader *parser = XMLReaderFactory::createXMLReader();
//    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
//    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional
//
//    auto* defaultHandler = new DefaultHandler();
//    parser->setContentHandler(defaultHandler);
//    parser->setErrorHandler(defaultHandler);
//
//    try {
//        parser->parse(filePath_.c_str());
//    }
//    catch (const XMLException& toCatch) {
//        char* message = XMLString::transcode(toCatch.getMessage());
//        std::cout << "Exception message is: \n"
//             << message << "\n";
//        XMLString::release(&message);
//        return;
//    }
//    catch (const SAXParseException& toCatch) {
//        char* message = XMLString::transcode(toCatch.getMessage());
//        std::cout << "Exception message is: \n"
//             << message << "\n";
//        XMLString::release(&message);
//        return;
//    }
//    catch (...) {
//        std::cout << "Unexpected Exception \n" ;
//        return;
//    }
//
//    delete parser;
//    delete defaultHandler;
//
//    XMLPlatformUtils::Terminate();




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

//    std::cout << "In file " << filePath_ << " " << allRecords_.size() << " unique records." << std::endl;
}

void XmlParser::writeDuplicateRecords() {
    if (!duplicateRecords_.empty()) {
        ::setlocale( LC_ALL , "russian_russia.866" );
        std::wcout.imbue(std::locale("ru_RU.UTF-8"));

        std::wcout << "\nDuplicate records:" << std::endl;
        for (const auto& [record, count] : duplicateRecords_) {
            std::wcout.imbue(std::locale("ru_RU.UTF8"));
            std::wcout << "city = " << record.city_ << ", street = " << record.street_ << ", house = " << record.house_
                      << ", floor = " << record.floor_ << " - occurs " << count << " times." << std::endl;
        }
    }
}

void XmlParser::writeCountBuildingsForEachCity() {
    if (!countBuildingsForEachCity_.empty()) {
        std::wcout << "\nCount buildings for each city:" << std::endl;
        for (const auto& [city, building] : countBuildingsForEachCity_) {
            std::wcout << "In the city " << city << ":" << std::endl;
            for (int i = 0; i < 5; ++i) {
                std::wcout << "\t" << building[i] << " " << i+1 << " floor houses" << std::endl;
            }
        }
    }
}

#endif //XMLANDCSVPARSER_XMLPARSER_H
