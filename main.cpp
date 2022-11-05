#include <iostream>
#include "XmlParser.h"

int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    XmlParser parser;
    std::string filename;
    std::cout << "Input file path" << std::endl;
    std::cin >> filename;
    std::cout << "Work started" << std::endl;
    parser.Read("/home/andrey/Projects/XmlAndCsvParser/data/" + filename);
    parser.writeDuplicateRecords();
    parser.writeCountBuildingsForEachCity();

//    std::wstring wstring(L"оооооох эта локаль");
//    std::wcout << L"абракадабра танцы с бубном" << std::endl;
//    std::wcout << wstring << std::endl;




    return 0;
}
