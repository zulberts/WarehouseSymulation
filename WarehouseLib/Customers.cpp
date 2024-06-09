#include "Customers.h"

Customer::Customer(const std::string& name, const std::string& lastname, int age)
    : Person(name, lastname, age) {}

PrivatePerson::PrivatePerson(const std::string& name, const std::string& lastname, int age)
    : Customer(name, lastname, age) {}

Firm::Firm(const std::string& firmName, const std::string& id, const std::string& country)
    : firmName(firmName), id(id), country(country) {}

std::string Firm::getFirmName() const {
    return firmName;
}

std::string Firm::getId() const {
    return id;
}

std::string Firm::getCountry() const {
    return country;
}