#pragma once
#include "Items.h"
#include "Customers.h"
#include "Transactions.h"
#include <string>
#include <vector>
#include <memory>

//DONE

class Document {
protected:
    std::vector<std::unique_ptr<Transaction>> transactions;

public:
    Document(const std::vector<std::unique_ptr<Transaction>>& transactions);
    virtual void GenerateDocument(const std::string& path) = 0;
    virtual ~Document() = default;
    std::string GetCurrentDateTime();
};

class Invoice : public Document {
private:
    std::string invoiceNumber;
    Worker seller;
    std::shared_ptr<Customer> customer;

public:
    Invoice(const std::string& invoiceNumber, const Worker& seller, std::shared_ptr<Customer> customer, const std::vector<std::unique_ptr<Transaction>>& transactions);
    void GenerateDocument(const std::string& path) override;
};

class Receipt : public Document {
private:
    std::string paymentMethod;
    std::shared_ptr<Customer> customer;

public:
    Receipt(const std::string& paymentMethod, std::shared_ptr<Customer> customer, const std::vector<std::unique_ptr<Transaction>>& transactions);
    void GenerateDocument(const std::string& path) override;
};
