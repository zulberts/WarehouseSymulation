#include "Transactions.h"
#include <algorithm>
#include <iomanip>

//DONE

Transaction::Transaction(std::vector<std::pair<Product, int>>& products, const Worker& worker, std::shared_ptr<Customer> customer)
    : products(products), worker(worker), customer(customer), canceled(false) {
    setTransactionTime();
}

double Transaction::calculateTotalPrice() const {
    double totalPrice = 0;
    for (const auto& item : products) {
        totalPrice += item.first.getPrice() * item.second;
    }

    return totalPrice;
}

double Transaction::calculateTax(double taxRate) const {
    return calculateTotalPrice() * taxRate;
}

void Transaction::cancel() {
    canceled = true;
}

bool Transaction::isCanceled() const {
    return canceled;
}

std::time_t Transaction::getTransactionTime() const {
    return transactionTime;
}

std::vector<std::pair<Product, int>> Transaction::getProducts() const {
    return products;
}

std::shared_ptr<Customer> Transaction::getCustomer() const {
    return customer;
}

const Worker& Transaction::getWorker() const {
    return worker;
}

void Transaction::setTransactionTime() {
    transactionTime = std::time(nullptr);
}


void TransactionRegister::addTransaction(std::unique_ptr<Transaction> transaction) {
    transactions.push_back(std::move(transaction));
}

void TransactionRegister::removeCanceledTransactions() {
    transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
        [](const std::unique_ptr<Transaction>& t) { return t->isCanceled(); }), transactions.end());
}

std::vector<Transaction*> TransactionRegister::filterByDate(std::time_t from, std::time_t to) const {
    std::vector<Transaction*> result;
    for (const auto& t : transactions) {
        if (t->getTransactionTime() >= from && t->getTransactionTime() <= to) {
            result.push_back(t.get());
        }
    }
    return result;
}

std::vector<Transaction*> TransactionRegister::filterByCustomer(const std::shared_ptr<Customer>& customer) const {
    std::vector<Transaction*> result;
    for (const auto& t : transactions) {
        if (t->getCustomer()->getName() == customer->getName()) {
            result.push_back(t.get());
        }
    }
    return result;
}

std::map<std::string, int> TransactionRegister::mostFrequentlySoldProducts() const {
    std::map<std::string, int> productFrequency;
    for (const auto& transaction : transactions) {
        for (const auto& item : transaction->getProducts()) {
            productFrequency[item.first.getName()] += item.second;
        }
    }
    return productFrequency;
}

const std::vector<std::unique_ptr<Transaction>>& TransactionRegister::getTransactions() const {
    return transactions;
}
