#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "Workers.h"

//DONE

enum class ProductType {
    Perishable,
    NonePerishable,
    Electronics,
    Apparel
};

class Item {
private:
    std::string name;
    double price;
    ProductType type;
    double tax;
    std::time_t expiryDate;

public:
    Item(const std::string& name, double price, const ProductType type, double tax, std::time_t expiryDate);

    std::string getName() const;
    double getPrice() const;
    ProductType getType() const;
    double getTax() const;
    std::time_t getExpiryDate() const;
};

struct ShipmentDetail {
    Item item;
    int quantity;
    std::time_t deliveryDate;
    ShipmentDetail(const Item& item, int quantity, std::time_t deliveryDate);
};

class Product {
private:
    Manager receivingManager;
    Worker storageWorker;
    std::time_t sale_date;
    bool is_sold;

public:
    ProductType type;
    std::string name;
    double price;
    double tax;
    std::string country;
    std::time_t validity_term;
    int weight;

    Product(const Manager& recManager, const Worker& storWorker, const std::string& name, double price, double tax, const std::string& country, std::time_t validity, int weight, ProductType type);

    std::time_t getSaleDate() const;
    void setSaleDate(std::time_t newSaleDate);
    bool isAvailable() const;
};

