#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Items.h" 

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products;

public:
    void addProduct(std::unique_ptr<Product> product);
    const std::vector<std::unique_ptr<Product>>& getProducts() const;

    std::vector<Product*> searchByName(const std::string& name) const;
    std::vector<Product*> searchByManufacturer(const std::string& manufacturer) const;
    std::vector<Product*> searchByExpiryDate(std::time_t expiryDate) const;
    std::vector<Product*> searchByType(ProductType type) const;
};
