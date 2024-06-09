#include "Transactions.h"
#include <fstream>
#include <iomanip>
#include <ctime>
#include <iostream>
#include <stdexcept>

Transaction::Transaction(std::vector<Product>& products, const Worker& worker, std::shared_ptr<Customer> customer)
    : products(products), worker(worker), customer(customer), canceled(false) {
    setTransactionTime();
    calculateTotalPriceAndTax();
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

std::vector<Product> Transaction::getProducts() const {
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

void Transaction::calculateTotalPriceAndTax() {
    totalprice = 0;
    totaltax = 0;
    for (const auto& item : products) {
        totalprice += item.getPrice();
        totaltax += item.getPrice() * item.getTax();
    }
}

std::string Transaction::getCurrentDateTime() const {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    char date[100];

    if (localtime_s(&tm, &t)) {
        throw std::runtime_error("Failed to get current time");
    }

    std::strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &tm);
    return date;
}

void Transaction::printDocument(const std::string& path, int index) {
    std::ofstream file;
    if (dynamic_cast<PrivatePerson*>(customer.get())) {
        file.open(path + "/paragon_" + std::to_string(index) + ".txt");
        file << "RECEIPT\n";
        file << "Date: " << getCurrentDateTime() << "\n";
        file << "--------------------------------------------------\n";
        file << std::left << std::setw(20) << "Product" << std::setw(10) << "Price" << std::setw(10) << "Tax" << std::setw(10) << "Total" << "\n";
        file << "--------------------------------------------------\n";
    }
    else {
        file.open(path + "/faktura_" + std::to_string(index) + ".txt");
        file << "INVOICE\n";
        file << "Invoice Number: " << index << "\n";
        file << "Issue Date: " << getCurrentDateTime() << "\n";
        file << "--------------------------------------------------\n";
        file << "Seller: " << worker.getName() << "\n";
        file << "--------------------------------------------------\n";
        file << "Buyer: " << dynamic_cast<Firm*>(customer.get())->getFirmName() << "\n";
        file << "--------------------------------------------------\n";
        file << std::left << std::setw(20) << "Product" << std::setw(10) << "Price" << std::setw(10) << "Tax" << std::setw(10) << "Total" << "\n";
        file << "--------------------------------------------------\n";
    }

    double totalAmount = 0;
    for (const auto& item : products) {
        double totalProductPrice = item.getPrice() + item.getPrice() * item.getTax();
        file << std::left << std::setw(20) << item.getName() << std::setw(10) << item.getPrice() << std::setw(10) << item.getTax() << std::setw(10) << totalProductPrice << "\n";
        totalAmount += totalProductPrice;
    }

    file << "--------------------------------------------------\n";
    file << std::left << std::setw(30) << "Total:" << totalAmount << "$\n";
    file.close();
    std::cout << "Document generated and saved to " << path << "\n";
}

double Transaction::getTotalPrice() const {
    return totalprice;
}

double Transaction::getTotalTax() const {
    return totaltax;
}