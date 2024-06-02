#pragma once
#include "Workers.h"
#include "Customers.h"
#include "Items.h"
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include <map>

class Transaction {
	//TODO
public:
    enum TransactionType { sale, purchase };

    Transaction(TransactionType type, const Product& product, int quantity, double summaryPrice, const Worker& worker, const Customer& customer);

    double calculateTax(double taxRate) const;
    double calculateDiscount(double discountRate) const;
    void cancel();
    bool isCanceled() const;
    int getQuantity() const;
    std::time_t getTransactionTime() const;
    TransactionType getType() const;
    const Product& getProduct() const;
    const Customer& getCustomer() const;

private:
    TransactionType type;
    const Product& product;
    int quantity;
    double summaryPrice;
    const Worker& worker;
    const Customer& customer;
    std::time_t transactionTime;
    bool canceled;
};

class TransactionRegister {
	//TODO
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(const Transaction& transaction);

    std::vector<Transaction> filterByDate(std::time_t from, std::time_t to) const;
    std::vector<Transaction> filterByCustomer(const Customer& customer) const;
    std::map<std::string, int> mostFrequentlySoldProducts() const;
};
