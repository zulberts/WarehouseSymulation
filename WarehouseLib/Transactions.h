#pragma once
#include "Workers.h"
#include "Customers.h"
#include "Items.h"
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <memory>
#include <fstream>

//DONE

class Transaction {
public:
    Transaction(std::vector<std::pair<Product, int>>& products, const Worker& worker, std::shared_ptr<Customer> customer);

    double calculateTotalPrice() const;
    double calculateTax(double taxRate) const;
    void cancel();
    bool isCanceled() const;
    std::time_t getTransactionTime() const;
    std::vector<std::pair<Product, int>> getProducts() const;
    std::shared_ptr<Customer> getCustomer() const;
    const Worker& getWorker() const;

    //Transaction(const Transaction&) = delete;
    //Transaction& operator=(const Transaction&) = delete;

private:

    std::vector<std::pair<Product, int>> products;
    const Worker& worker;
    std::shared_ptr<Customer> customer;
    std::time_t transactionTime;
    bool canceled;
    void setTransactionTime();
};

class TransactionRegister {
private:
    std::vector<std::unique_ptr<Transaction>> transactions;

public:
    void addTransaction(std::unique_ptr<Transaction> transaction);
    void removeCanceledTransactions();

    std::vector<Transaction*> filterByDate(std::time_t from, std::time_t to) const;
    std::vector<Transaction*> filterByCustomer(const std::shared_ptr<Customer>& customer) const;
    std::map<std::string, int> mostFrequentlySoldProducts() const;
    const std::vector<std::unique_ptr<Transaction>>& getTransactions() const;
};
