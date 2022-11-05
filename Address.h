#ifndef XMLANDCSVPARSER_ADDRESS_H
#define XMLANDCSVPARSER_ADDRESS_H

#include <string>

class Address {
public:
    const std::wstring city_;
    const std::wstring street_;
    const std::wstring house_;
    const std::wstring floor_;

    Address(const std::wstring &city, const std::wstring &street, const std::wstring &house, const std::wstring &floor)
        : city_(city), street_(street), house_(house), floor_(floor) { }

    Address(std::wstring &&city, std::wstring &&street, std::wstring &&house, std::wstring &&floor)
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
