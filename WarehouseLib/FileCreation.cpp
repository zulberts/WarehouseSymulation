#include "FileCreation.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

std::string Document::GetCurrentDateTime() {
    std::time_t t = std::time(nullptr);
    char date[100];
    std::strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return date;
}


Invoice::Invoice(const std::string& invoiceNumber, const Person& seller, const Customer& customer)
    : invoiceNumber(invoiceNumber), seller(seller), customer(customer) {}


void Invoice::GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << "INVOICE" << std::endl;
        file << "Invoice Number: " << invoiceNumber << std::endl;
        file << "Issue Date: " << GetCurrentDateTime() << std::endl;
        file << "------------------------------------" << std::endl;
        file << "Seller: " << seller.getName() << " " << seller.getLastName() << std::endl;
        file << "------------------------------------" << std::endl;
        file << "Buyer: " << customer.getName() << " " << customer.getLastName() << std::endl;
        file << "------------------------------------" << std::endl;
        file << std::left << std::setw(20) << "Product" << std::setw(10) << "Unit Price" << std::setw(10) << "Quantity" << std::setw(10) << "Tax Rate" << std::setw(10) << "Total" << std::endl;
        file << "------------------------------------" << std::endl;
        double totalNet = 0;
        double totalTax = 0;
        for (const auto& detail : products) {
            double netPrice = detail.item.getPrice() * detail.quantity;
            double taxAmount = detail.item.getTax() * detail.quantity;
            double totalPrice = netPrice + taxAmount;
            file << std::left << std::setw(20) << detail.item.getName() << std::setw(10) << detail.item.getPrice() << std::setw(10) << detail.quantity << std::setw(10) << detail.item.getTax() << std::setw(10) << totalPrice << std::endl;
            totalNet += netPrice;
            totalTax += taxAmount;
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
    }
}


void Receipt::GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path) {
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
        for (const auto& detail : products) {
            double totalProductPrice = (detail.item.getPrice() + detail.item.getTax()) * detail.quantity;
            file << std::left << std::setw(20) << detail.item.getName() << std::setw(10) << detail.item.getPrice() << std::setw(10) << totalProductPrice << std::setw(10) << detail.quantity << std::endl;
            totalAmount += detail.item.getPrice() * detail.quantity;
            totalTax += detail.item.getTax() * detail.quantity;
        }
        file << "--------------------------------------------------" << std::endl;
        file << std::left << std::setw(30) << "Total:" << (totalAmount + totalTax) << "$" << std::endl;
        file.close();
        std::cout << "Receipt generated and saved to " << path << std::endl;
    }
    else {
        std::cerr << "Unable to open file for saving receipt." << std::endl;
    }
}

void Receipt::GenerateDocument(const std::vector<ShipmentDetail>& products, const std::string& path, const std::string& paymentMethod) {
    this->paymentMethod = paymentMethod;
    GenerateDocument(products, path);
}
