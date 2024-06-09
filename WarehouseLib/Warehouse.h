#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Items.h"
#include "Transactions.h"
#include "Workers.h"
#include "Shipment.h"
#include "Customers.h"

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products;
    std::vector<std::unique_ptr<Shipment>> shipments;
    std::vector<std::unique_ptr<Worker>> workers;
    std::vector<std::unique_ptr<Manager>> managers;
    std::vector<std::unique_ptr<Transaction>> transactions;
    std::vector<FirmCustomer> firms;

public:
    Warehouse();

    const std::vector<std::unique_ptr<Product>>& getProducts() const;
    const std::vector<std::unique_ptr<Shipment>>& getShipments() const;
    const std::vector<std::unique_ptr<Worker>>& getWorkers() const;
    const std::vector<std::unique_ptr<Manager>>& getManagers() const;
    const std::vector<std::unique_ptr<Transaction>>& getTransactions() const;

    void addShipment(std::unique_ptr<Shipment> shipment);
    void addWorker(std::unique_ptr<Worker> worker);
    void addManager(std::unique_ptr<Manager> manager);
    void addTransaction(const std::vector<ShipmentDetail>& items, std::shared_ptr<Customer> customer, const Worker& worker);

    Product* searchByName(const std::string& name) const;
    Product* searchByManufacturer(const std::string& manufacturer) const;
    Product* searchByExpiryDate(std::time_t expiryDate) const;
    Product* searchByType(ProductType type) const;

    void generateDocument(const std::string& path);

    void saveToJson(const std::string& filename) const;
    void loadFromJson(const std::string& filename);

    void listWorkers() const;
    bool fireWorker(size_t index);

    void makePurchase();
    std::shared_ptr<Customer> createCustomer(bool isFirm);

    void addShipmentAsManager(const std::vector<ShipmentDetail>& items, const Manager& manager, const Worker& worker);
};
