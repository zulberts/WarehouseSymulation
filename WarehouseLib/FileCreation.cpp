#include "FileCreation.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

Document::Document(const std::vector<std::unique_ptr<Transaction>>& transactions) {
    for (const auto& transaction : transactions) {
        this->transactions.push_back(std::make_unique<Transaction>(*transaction));
    }
}

std::string Document::GetCurrentDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    char date[100];

    if (localtime_s(&tm, &t)) {
        throw std::runtime_error("Failed to get current time");
    }

    std::strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", &tm);
    return date;
}

Invoice::Invoice(const std::string& invoiceNumber, const Worker& seller, std::shared_ptr<Customer> customer, const std::vector<std::unique_ptr<Transaction>>& transactions)
    : invoiceNumber(invoiceNumber), seller(seller), customer(customer), Document(transactions) {}

void Invoice::GenerateDocument(const std::string& path) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << "INVOICE" << std::endl;
        file << "Invoice Number: " << invoiceNumber << std::endl;
        file << "Issue Date: " << GetCurrentDateTime() << std::endl;
        file << "------------------------------------" << std::endl;
        file << "Seller: " << seller.getName() << std::endl;
        file << "------------------------------------" << std::endl;
        file << "Buyer: " << customer->getName() << std::endl;
        file << "------------------------------------" << std::endl;
        file << std::left << std::setw(20) << "Product" << std::setw(10) << "Summary Price" << std::setw(10) << "Quantity" << std::setw(10) << "Tax Rate" << std::setw(10) << "Total" << std::endl;
        file << "------------------------------------" << std::endl;
        double totalNet = 0;
        double totalTax = 0;
        for (const auto& transaction : transactions) {
            for (const auto& pair : transaction->getProducts()) {
                double netPrice = pair.first.getPrice() * pair.second;
                double taxAmount = pair.first.getTax() * pair.second;
                double totalPrice = netPrice + taxAmount;
                file << std::left << std::setw(20) << pair.first.getName() << std::setw(10) << pair.first.getPrice() << std::setw(10) << pair.second << std::setw(10) << pair.first.getTax() << std::setw(10) << totalPrice << std::endl;
                totalNet += netPrice;
                totalTax += taxAmount;
            }
        }
        file << "------------------------------------" << std::endl;
        file << std::left << std::setw(20) << "Total Net Amount:" << totalNet << "$" << std::endl;
        file << std::left << std::setw(20) << "Total Tax Amount:" << totalTax << "$" << std::endl;
        file << std::left << std::setw(20) << "Total Amount Due:" << (totalNet + totalTax) << "$" << std::endl;
        file.close();
        std::cout << "Invoice generated and saved to " << path << std::endl;
    }
    else {
        std::cerr << "Unable to open file for saving invoice." << std::endl;
        std::terminate();
    }
}

Receipt::Receipt(const std::string& paymentMethod, std::shared_ptr<Customer> customer, const std::vector<std::unique_ptr<Transaction>>& transactions)
    : paymentMethod(paymentMethod), customer(customer), Document(transactions) {}

void Receipt::GenerateDocument(const std::string& path) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << "RECEIPT" << std::endl;
        file << "Date: " << GetCurrentDateTime() << std::endl;
        file << "Payment Method: " << paymentMethod << std::endl;
        file << "--------------------------------------------------" << std::endl;
        file << std::left << std::setw(20) << "Product" << std::setw(10) << "Price" << std::setw(10) << "Total" << std::setw(10) << "Quantity" << std::endl;
        file << "--------------------------------------------------" << std::endl;
        double totalAmount = 0;
        double totalTax = 0;
        for (const auto& transaction : transactions) {
            for (const auto& pair : transaction->getProducts()) {
                double totalProductPrice = (pair.first.getPrice() + pair.first.getTax()) * pair.second;
                file << std::left << std::setw(20) << pair.first.getName() << std::setw(10) << pair.first.getPrice() << std::setw(10) << totalProductPrice << std::setw(10) << pair.second << std::endl;
                totalAmount += pair.first.getPrice() * pair.second;
                totalTax += pair.first.getTax() * pair.second;
            }
        }
        file << "--------------------------------------------------" << std::endl;
        file << std::left << std::setw(30) << "Total:" << (totalAmount + totalTax) << "$" << std::endl;
        file.close();
        std::cout << "Receipt generated and saved to " << path << std::endl;
    }
    else {
        std::cerr << "Unable to open file for saving receipt." << std::endl;
        std::terminate();
    }
}
