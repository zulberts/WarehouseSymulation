#pragma once
#include "Items.h"
#include "Customers.h"
#include "Transactions.h"
#include <string>
#include <vector>
#include <memory>

//DONE

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
    std::shared_ptr<Customer> customer;

public:
    Invoice(const std::string& invoiceNumber, const Person& seller, std::shared_ptr<Customer> customer);
    void GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path) override;
};

class Receipt : public Document {
private:
    std::string paymentMethod;
    std::shared_ptr<Customer> customer;

public:
    Receipt(const std::string& paymentMethod, std::shared_ptr<Customer> customer);
    void GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path) override;
    void GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path, const std::string& paymentMethod);
};
