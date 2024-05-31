#include "Transactions.h"
#include <algorithm>
#include <iomanip>

Transaction::Transaction(TransactionType type, const Product& product, int quantity, double summaryPrice, const Worker& worker, const Customer& customer)
    : type(type), product(product), quantity(quantity), summaryPrice(summaryPrice), worker(worker), customer(customer), canceled(false) {
    transactionTime = std::time(nullptr);
}

double Transaction::calculateTax(double taxRate) const {
    return quantity * summaryPrice * taxRate;
}

double Transaction::calculateDiscount(double discountRate) const {
    return quantity * summaryPrice * discountRate;
}

void Transaction::cancel() {
    canceled = true;
}

bool Transaction::isCanceled() const {
    return canceled;
}

int Transaction::getQuantity() const
{
    return quantity;
}

std::time_t Transaction::getTransactionTime() const {
    return transactionTime;
}

Transaction::TransactionType Transaction::getType() const {
    return type;
}

const Product& Transaction::getProduct() const {
    return product;
}

const Customer& Transaction::getCustomer() const {
    return customer;
}


void TransactionRegister::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

std::vector<Transaction> TransactionRegister::filterByDate(std::time_t from, std::time_t to) const {
    std::vector<Transaction> result;
    std::copy_if(transactions.begin(), transactions.end(), std::back_inserter(result), [from, to](const Transaction& t) {
        return t.getTransactionTime() >= from && t.getTransactionTime() <= to;
        });
    return result;
}

std::vector<Transaction> TransactionRegister::filterByCustomer(const Customer& customer) const {
    std::vector<Transaction> result;
    std::copy_if(transactions.begin(), transactions.end(), std::back_inserter(result), [customer](const Transaction& t) {
        return t.getCustomer().getName() == customer.getName();
        });
    return result;
}

std::map<std::string, int> TransactionRegister::mostFrequentlySoldProducts() const {
    std::map<std::string, int> products;
    for (const auto& transaction : transactions) {
        if (transaction.getType() == Transaction::sale && !transaction.isCanceled()) {
            products[transaction.getProduct().name] += transaction.getQuantity();
        }
    }
    return products;
}
