#ifndef XMLANDCSVPARSER_MYSAX2HANDLER_H
#define XMLANDCSVPARSER_MYSAX2HANDLER_H

#include <xercesc/sax/HandlerBase.hpp>
#include <iostream>

class MySAXHandler : public xercesc::HandlerBase {
private:
    int numSeq_;
public:
    MySAXHandler() = default;
    ~MySAXHandler() = default;

    void startElement(const XMLCh* const name, xercesc::AttributeList& attrs);
    void endElement(const XMLCh* const name);
    void characters(const XMLCh* const data, const XMLSize_t length);
    void fatalError(const xercesc::SAXParseException& exception);
};

void MySAXHandler::startElement(const XMLCh *const name, xercesc::AttributeList &attrs) {
    numSeq_++;
    std::cout << numSeq_ << "\t-> Start : " << name << std::endl;

    XMLSize_t len = attrs.getLength();
}

void MySAXHandler::fatalError(const xercesc::SAXParseException & exception) {
    std::cout << "Fatal Error: " << exception.getMessage() << " at line: "
        << exception.getLineNumber() << std::endl;
}

void MySAXHandler::endElement(const XMLCh *const name) {
    numSeq_++;
    std::cout << numSeq_ << "\t-> End: " << name << std::endl;
}

void MySAXHandler::characters(const XMLCh *const data, const XMLSize_t length) {
    numSeq_++;
    std::cout << numSeq_ << "\t-> Data: " << data << std::endl;
}

#endif //XMLANDCSVPARSER_MYSAX2HANDLER_H
