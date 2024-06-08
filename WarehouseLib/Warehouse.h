#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <fstream>
#include "Items.h"
#include "Transactions.h"
#include "Workers.h"
#include "Shipment.h"
#include "FileCreation.h"

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products;
    TransactionRegister transactionRegister;
    std::vector<std::unique_ptr<Shipment>> shipments;
    std::vector<std::unique_ptr<Worker>> workers;
    Manager* manager;

public:
    Warehouse() : manager(nullptr) {}
    Warehouse(Manager* manager) : manager(manager) {}

    void addProduct(std::unique_ptr<Product> product);
    const std::vector<std::unique_ptr<Product>>& getProducts() const;

    std::vector<Product*> searchByName(const std::string& name) const;
    std::vector<Product*> searchByManufacturer(const std::string& manufacturer) const;
    std::vector<Product*> searchByExpiryDate(std::time_t expiryDate) const;
    std::vector<Product*> searchByType(ProductType type) const;

    void addTransaction(std::unique_ptr<Transaction> transaction);
    const std::vector<std::unique_ptr<Transaction>>& getTransactions() const;

    void addWorker(std::unique_ptr<Worker> worker);
    const std::vector<std::unique_ptr<Worker>>& getWorkers() const;

    void addShipment(std::unique_ptr<Shipment> shipment);
    const std::vector<std::unique_ptr<Shipment>>& getShipments() const;

    void applyDiscounts(double discountRate, std::time_t daysBeforeExpiry);

    void generateInvoice(const std::string& invoiceNumber, const Person& seller, std::shared_ptr<Customer> customer, const std::string& path, const std::vector<Transaction*>& transactions);
    void generateReceipt(const std::string& paymentMethod, std::shared_ptr<Customer> customer, const std::string& path, const std::vector<Transaction*>& transactions);


    void saveToJson(const std::string& filename) const; 
    void loadFromJson(const std::string& filename); 

    void listWorkers() const;
    bool fireWorker(size_t index);
};
