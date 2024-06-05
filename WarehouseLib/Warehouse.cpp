#include "Warehouse.h"

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    products.push_back(std::move(product));
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
