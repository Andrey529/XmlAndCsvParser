#ifndef XMLANDCSVPARSER_ADDRESS_H
#define XMLANDCSVPARSER_ADDRESS_H

#include <string>

template<class value_type = std::wstring>
class Address {
public:
    const value_type city_;
    const value_type street_;
    const value_type house_;
    const value_type floor_;

    Address(const value_type &city, const value_type &street, const value_type &house, const value_type &floor)
        : city_(city), street_(street), house_(house), floor_(floor) { }

    Address(value_type &&city, value_type &&street, value_type &&house, value_type &&floor)
            : city_(std::move(city)), street_(std::move(street)), house_(std::move(house)), floor_(std::move(floor)) { }
};

template<class value_type = std::wstring>
bool operator==(const Address<value_type>& lhs, const Address<value_type>& rhs) {
    return (lhs.city_ == rhs.city_) &&
           (lhs.street_ == rhs.street_) &&
           (lhs.house_ == rhs.house_) &&
           (lhs.floor_ == rhs.floor_);
}

template<class value_type = std::wstring>
bool operator<(const Address<value_type> &lhs, const Address<value_type> &rhs) {
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

template<class value_type = std::wstring>
struct AddressHasher {
    std::size_t operator()(const Address<value_type> &address) const {
        size_t res = 17;
        res = res * 31 + std::hash<value_type>()( address.city_ );
        res = res * 31 + std::hash<value_type>()( address.street_ );
        res = res * 31 + std::hash<value_type>()( address.house_ );
        res = res * 31 + std::hash<value_type>()( address.floor_ );
        return res;
    }
};

#endif //XMLANDCSVPARSER_ADDRESS_H
