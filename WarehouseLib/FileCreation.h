#pragma once
#include "Items.h"
#include "Customers.h"
#include <string>
#include <vector>

class Document {
public:
    virtual void GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path) = 0;
    virtual ~Document() = default;
    std::string GetCurrentDateTime();
};

class Invoice : public Document {
private:
    std::string invoiceNumber;
    Person seller;
    Customer customer;

public:
    Invoice(const std::string& invoiceNumber, const Person& seller, const Customer& customer);
    void GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path) override;
    //TODO: Add any additional member functions needed
};

class Receipt : public Document {
private:
    std::string paymentMethod;

public:
    void GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path) override;
    void GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path, const std::string& paymentMethod);
    //TODO: Add any additional member functions needed
};
