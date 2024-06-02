#pragma once
#include <string>
#include <vector>
#include "Items.h"
#include "Person.h"

class Customer : public Person {
protected:
    std::vector<Product> purchaseHistory;

public:
    Customer(const std::string& name, const std::string& lastname, int age);

    void addPurchase(const Product& product);
    virtual double calculateDiscount() const;
    std::string getPurchaseHistory() const;
};

class PrivatePerson : public Customer {
protected:
    std::vector<Item> purchasePreferences;

public:
    PrivatePerson(const std::string& name, const std::string& lastname, int age);

    void addPreference(const Item& preference);
    Item getPreference(ProductType type) const;
    double calculateDiscount() const override;
};

class Firm : public Customer {
private:
    std::string firmName;
    std::string id;
    std::string exchange;

public:
    Firm(const std::string& name, const std::string& lastname, int age,
        const std::string& firmName, const std::string& id, const std::string& exchange);

    std::string getFirmName() const;
    std::string getId() const;
    std::string getExchange() const;
    double calculateDiscount() const override;
};
