#ifndef XMLANDCSVPARSER_ADDRESS_H
#define XMLANDCSVPARSER_ADDRESS_H

#include <string>

class Address {
public:
    const std::string city_;
    const std::string street_;
    const std::string house_;
    const std::string floor_;

    Address(const std::string &city, const std::string &street, const std::string &house, const std::string &floor)
        : city_(city), street_(street), house_(house), floor_(floor) { }

    Address(std::string &&city, std::string &&street, std::string &&house, std::string &&floor)
            : city_(std::move(city)), street_(std::move(street)), house_(std::move(house)), floor_(std::move(floor)) { }
};

bool operator<(const Address &lhs, const Address &rhs) {
    if (lhs.city_ < rhs.city_)
        return true;
    else if (lhs.city_ > rhs.city_)
        return false;
    else {
        if (lhs.street_ < rhs.street_)
            return true;
        else if (lhs.street_ > rhs.street_)
            return false;
        else {
            if (lhs.house_ < rhs.house_)
                return true;
            else if (lhs.house_ > rhs.house_)
                return false;
            else {
                if (lhs.floor_ < rhs.floor_)
                    return true;
                else if (lhs.floor_ > rhs.floor_)
                    return false;
                else
                    return false;
            }
        }
    }
}

#endif //XMLANDCSVPARSER_ADDRESS_H
