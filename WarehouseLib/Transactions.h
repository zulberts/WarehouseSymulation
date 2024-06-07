#pragma once
#include "Workers.h"
#include "Customers.h"
#include "Items.h"
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

//DONE

class Transaction {
public:
    Transaction(const Product& product, int quantity, double summaryPrice, const Worker& worker, std::shared_ptr<Customer> customer);

    double calculateTax(double taxRate) const;
    double calculateDiscount(double discountRate) const;
    void cancel();
    bool isCanceled() const;
    int getQuantity() const;
    std::time_t getTransactionTime() const;
    const Product& getProduct() const;
    std::shared_ptr<Customer> getCustomer() const;

    double getSummaryPrice() const;
    const Worker& getWorker() const;

    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;

private:
    const Product& product;
    int quantity;
    double summaryPrice;
    const Worker& worker;
    std::shared_ptr<Customer> customer;
    std::time_t transactionTime;
    bool canceled;
    void setTransactionTime();
};

class TransactionRegister {
private:
    std::vector<std::unique_ptr<Transaction>> transactions;
    std::vector<std::unique_ptr<Transaction>> canceledTransactions;

public:
    void addTransaction(std::unique_ptr<Transaction> transaction);
    void removeCanceledTransactions();
    void restoreTransaction(std::unique_ptr<Transaction> transaction);

    std::vector<Transaction*> filterByDate(std::time_t from, std::time_t to) const;
    std::vector<Transaction*> filterByCustomer(const std::shared_ptr<Customer>& customer) const;
    std::map<std::string, int> mostFrequentlySoldProducts() const;
    const std::vector<std::unique_ptr<Transaction>>& getCanceledTransactions() const;
    const std::vector<std::unique_ptr<Transaction>>& getTransactions() const;
};
