#ifndef XMLANDCSVPARSER_APP_H
#define XMLANDCSVPARSER_APP_H

#include <string>
#include <iostream>
#include <chrono>
#include "XmlParser.h"
#include "CsvParser.h"

class App {
private:
    enum class EXIT_STATUS {
        CONTINUE,
        EXIT
    };

    std::string filePath_;
    EXIT_STATUS exitStatus_ = EXIT_STATUS::CONTINUE;
public:
    App() = default;
    void Run() {
        int attemptForInputFilePath = 3;
        while (exitStatus_ == EXIT_STATUS::CONTINUE) {
            std::cout << "Enter a file path:" << std::endl;
            std::cin >> filePath_;

            if (filePath_.find(".xml") != std::string::npos) {
                attemptForInputFilePath = 3;
                XmlParser parser;
                std::cout << "Work started" << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                parser.Read(filePath_);
                auto finish = std::chrono::duration_cast<std::chrono::nanoseconds>
                            (std::chrono::high_resolution_clock::now() - start);
                double time = finish.count();
                std::cout << "File processing time = " << time << " ns = " << time/1000000000 << " sec." << std::endl;
                parser.writeDuplicateRecords();
                parser.writeCountBuildingsForEachCity();
            }
            else if (filePath_.find(".csv") != std::string::npos) {
                attemptForInputFilePath = 3;

                CsvParser parser;
                std::cout << "Work started" << std::endl;

                auto start = std::chrono::high_resolution_clock::now();
                parser.Read(filePath_);
                auto finish = std::chrono::duration_cast<std::chrono::nanoseconds>
                        (std::chrono::high_resolution_clock::now() - start);
                double time = finish.count();
                std::cout << "File processing time = " << time << " ns = " << time/1000000000 << " sec." << std::endl;
                parser.writeDuplicateRecords();
                parser.writeCountBuildingsForEachCity();
            }
            else {
                attemptForInputFilePath--;
                std::cout << "Invalid file path." << std::endl;
                if (attemptForInputFilePath > 0) {
                    std::cout << "Please enter correct path." << std::endl;
                }
                else {
                    break;
                }
                continue;
            }

            std::cout << "Do you want to continue the program?" << std::endl;
            std::string answer;
            std::cin >> answer;
            if (answer == "yes" || answer == "Yes" || answer == "YES" || answer == "y" || answer == "Y") {
                exitStatus_ = EXIT_STATUS::CONTINUE;
            }
            else {
                exitStatus_ = EXIT_STATUS::EXIT;
            }
        }
    }
};

#endif //XMLANDCSVPARSER_APP_H
