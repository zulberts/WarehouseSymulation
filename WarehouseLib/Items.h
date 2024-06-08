#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "Workers.h"
#include "Customers.h"

enum class ProductType {
    Perishable,
    NonPerishable,
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
    int weight;
    Firm firm;

public:
    Item(const std::string& name, double price, const ProductType type, double tax, std::time_t expiryDate, int weight, const Firm& firm);

    std::string getName() const;
    double getPrice() const;
    ProductType getType() const;
    double getTax() const;
    std::time_t getExpiryDate() const;
    int getWeight() const;
    Firm getFirm() const;
};

struct ShipmentDetail {
    Item item;
    int quantity;
    ShipmentDetail(const Item& item, int quantity);
};

class Product : public Item {
private:
    Manager receivingManager;
    Worker storageWorker;
    std::time_t saleDate;
    bool isSold;

public:
    Product(const Manager& recManager, const Worker& storWorker, const std::string& name, double price, double tax, const Firm& firm, std::time_t expiryDate, int weight, ProductType type);

    std::time_t getSaleDate() const;
    void setSaleDate(std::time_t newSaleDate);
    bool isAvailable() const;
};