#include <iostream>
#include "XmlParser.h"

int main() {

    XmlParser parser;
    std::string filename;
    std::cin >> filename;
    parser.Read("/home/andrey/Projects/XmlAndCsvParser/data/" + filename);
    parser.writeDuplicateRecords();
    return 0;
}
