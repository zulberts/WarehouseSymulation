#pragma once
#include <string>
#include "Person.h"

class Customer : public Person {
public:
    Customer(const std::string& name, const std::string& lastname, int age);
};

class PrivatePerson : public Customer {
public:
    PrivatePerson(const std::string& name, const std::string& lastname, int age);
};

class Firm {
private:
    std::string firmName;
    std::string id;
    std::string country;

public:
    Firm(const std::string& firmName, const std::string& id, const std::string& country);

    std::string getFirmName() const;
    std::string getId() const;
    std::string getCountry() const;
};