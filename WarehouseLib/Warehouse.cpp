#include "Warehouse.h"

//DONE

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    products.push_back(std::move(product));
}

const std::vector<std::unique_ptr<Product>>& Warehouse::getProducts() const {
    return products;
}

std::vector<Product*> Warehouse::searchByName(const std::string& name) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->name == name) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByManufacturer(const std::string& manufacturer) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->country == manufacturer) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByExpiryDate(std::time_t expiryDate) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->validity_term == expiryDate) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByType(ProductType type) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->type == type) {
            result.push_back(product.get());
        }
    }
    return result;
}

void Warehouse::addTransaction(std::unique_ptr<Transaction> transaction) {
    transactionRegister.addTransaction(std::move(transaction));
}

const std::vector<std::unique_ptr<Transaction>>& Warehouse::getTransactions() const {
    return transactionRegister.getTransactions();
}

void Warehouse::addWorker(std::unique_ptr<Worker> worker) {
    workers.push_back(std::move(worker));
}

const std::vector<std::unique_ptr<Worker>>& Warehouse::getWorkers() const {
    return workers;
}

void Warehouse::addShipment(std::unique_ptr<Shipment> shipment) {
    shipments.push_back(std::move(shipment));
}

const std::vector<std::unique_ptr<Shipment>>& Warehouse::getShipments() const {
    return shipments;
}

void Warehouse::applyDiscounts(double discountRate, std::time_t daysBeforeExpiry) {
    std::time_t currentTime = std::time(nullptr);
    for (auto& product : products) {
        if (std::difftime(product->validity_term, currentTime) <= daysBeforeExpiry * 24 * 60 * 60) {
            product->price -= product->price * discountRate;
        }
    }
}

void Warehouse::generateInvoice(const std::string& invoiceNumber, const Person& seller, std::shared_ptr<Customer> customer, const std::string& path) {
    if (std::dynamic_pointer_cast<Firm>(customer)) {
        std::vector<ShipmentDetail> products;  // Fill this with relevant products.
        Invoice invoice(invoiceNumber, seller, customer);
        invoice.GenerateDocument(products, path);
    }
    else {
        throw std::invalid_argument("Customer is not eligible for an invoice.");
    }
}

void Warehouse::generateReceipt(const std::string& paymentMethod, std::shared_ptr<Customer> customer, const std::string& path) {
    if (std::dynamic_pointer_cast<PrivatePerson>(customer)) {
        std::vector<ShipmentDetail> products;  // Fill this with relevant products.
        Receipt receipt(paymentMethod, customer);
        receipt.GenerateDocument(products, path);
    }
    else {
        throw std::invalid_argument("Customer is not eligible for a receipt.");
    }
}
