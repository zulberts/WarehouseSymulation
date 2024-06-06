#include "DataTransfer.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Items.h"

void DataTransfer::saveToJson(const Warehouse& warehouse, const std::string& filename) {
    nlohmann::json j;

    for (const auto& productPtr : warehouse.getProducts()) {
        const Product& product = *productPtr;
        nlohmann::json jProduct;

        jProduct["type"] = static_cast<int>(product.type);
        jProduct["name"] = product.name;
        jProduct["price"] = product.price;
        jProduct["tax"] = product.tax;
        jProduct["country"] = product.country;
        jProduct["validity_term"] = product.validity_term;
        jProduct["weight"] = product.weight;
        jProduct["sale_date"] = product.getSaleDate();
        jProduct["is_sold"] = product.isAvailable();

        j["products"].push_back(jProduct);
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
    else {
        throw std::runtime_error("Unable to open file for writing");
    }
}

Warehouse DataTransfer::loadFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for reading");
    }

    nlohmann::json j;
    file >> j;
    file.close();

    Warehouse warehouse;

    for (const auto& jProduct : j["products"]) {
        Manager manager("Default", "Manager", 0, 0.0, 0);
        Worker worker("Default", "Worker", 0, Post::PhysicalLabor, 0.0, 0);

        Product product(
            manager,
            worker,
            jProduct["name"].get<std::string>(),
            jProduct["price"].get<double>(),
            jProduct["tax"].get<double>(),
            jProduct["country"].get<std::string>(),
            jProduct["validity_term"].get<std::time_t>(),
            jProduct["weight"].get<int>(),
            static_cast<ProductType>(jProduct["type"].get<int>())
        );

        product.setSaleDate(jProduct["sale_date"].get<std::time_t>());
        warehouse.addProduct(std::make_unique<Product>(product));
    }

    return warehouse;
}
