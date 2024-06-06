#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Items.h" 
#include "Transactions.h"
#include "Workers.h"

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products;
    std::vector<Transaction> transactions;
    Manager* manager;

public:

    Warehouse() : manager(nullptr), transactions() {}
    Warehouse(Manager* manager) : manager(manager), transactions() {}

    void addProduct(std::unique_ptr<Product> product);
    const std::vector<std::unique_ptr<Product>>& getProducts() const;

    std::vector<Product*> searchByName(const std::string& name) const;
    std::vector<Product*> searchByManufacturer(const std::string& manufacturer) const;
    std::vector<Product*> searchByExpiryDate(std::time_t expiryDate) const;
    std::vector<Product*> searchByType(ProductType type) const;

    void addTransaction(const Transaction& transaction);
    const std::vector<Transaction>& getTransactions() const;
};
