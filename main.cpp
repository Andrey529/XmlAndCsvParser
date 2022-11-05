#include <iostream>
#include "XmlParser.h"

int main() {

    XmlParser parser;
    std::string filename;
    std::cout << "Input file path" << std::endl;
    std::cin >> filename;
    std::cout << "Work started" << std::endl;
    parser.Read("/home/andrey/Projects/XmlAndCsvParser/data/" + filename);
    parser.writeDuplicateRecords();
    parser.writeCountBuildingsForEachCity();

    return 0;
}
