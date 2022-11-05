cmake_minimum_required(VERSION 3.23)
project(XmlAndCsvParser)

set(CMAKE_CXX_STANDARD 20)

add_executable(XmlAndCsvParser main.cpp XmlParser.h Address.h App.h)
