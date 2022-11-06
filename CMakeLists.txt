cmake_minimum_required(VERSION 3.23)
project(XmlAndCsvParser)

set(CMAKE_CXX_STANDARD 20)

# Clone csv-parser
set(CSVPARSER_DIR ${CMAKE_SOURCE_DIR}/external/lib/csvparser)
if(NOT EXISTS ${CSVPARSER_DIR})
    find_package(Git REQUIRED)
    execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule add https://github.com/vincentlaucsb/csv-parser.git ${CSVPARSER_DIR}
    )
endif()
# Add the csv-parser CMake files to the project
add_subdirectory(${CSVPARSER_DIR})
include_directories(${CSVPARSER_DIR}/include)

add_executable(XmlAndCsvParser main.cpp XmlParser.h Address.h App.h CsvParser.h)

# Link the csv-parser library with our executable
target_link_libraries(XmlAndCsvParser csv)