#pragma once
#include "Workers.h"
#include "Customers.h"
#include "Items.h"
#include <vector>
#include <memory>
#include <ctime>

class Transaction {
public:
    Transaction(std::vector<Product>& products, const Worker& worker, std::shared_ptr<Customer> customer);
    void cancel();
    bool isCanceled() const;
    std::time_t getTransactionTime() const;
    std::vector<Product> getProducts() const;
    std::shared_ptr<Customer> getCustomer() const;
    const Worker& getWorker() const;
    void printDocument(const std::string& path, int index);

private:
    std::vector<Product> products;
    const Worker& worker;
    std::shared_ptr<Customer> customer;
    std::time_t transactionTime;
    double totalprice;
    double totaltax;
    bool canceled;
    void setTransactionTime();
    void calculateTotalPriceAndTax();
    std::string getCurrentDateTime() const;
};
