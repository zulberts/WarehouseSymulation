#include "Items.h"
#include "Workers.h"
#include <ctime>

//DONE

Item::Item(const std::string& name, double price, const ProductType type, double tax, std::time_t expiryDate)
    : name(name), price(price), type(type), tax(tax), expiryDate(expiryDate) {}

std::string Item::getName() const {
    return name;
}

double Item::getPrice() const {
    return price;
}

ProductType Item::getType() const {
    return type;
}

double Item::getTax() const {
    return tax;
}

std::time_t Item::getExpiryDate() const {
    return expiryDate;
}

ShipmentDetail::ShipmentDetail(const Item& item, int quantity, std::time_t deliveryDate)
    : item(item), quantity(quantity), deliveryDate(deliveryDate) {}

Product::Product(const Manager& recManager, const Worker& storWorker, const std::string& name, double price, double tax, const std::string& country, std::time_t validity, int weight, ProductType type)
    : receivingManager(recManager), storageWorker(storWorker), name(name), price(price), tax(tax), country(country), validity_term(validity), weight(weight), type(type), is_sold(false) {
    sale_date = std::time(nullptr);
}

std::time_t Product::getSaleDate() const {
    return sale_date;
}

void Product::setSaleDate(std::time_t newSaleDate) {
    sale_date = newSaleDate;
    validity_term = sale_date;
}

bool Product::isAvailable() const {
    std::time_t currentTime = std::time(nullptr);
    return currentTime < validity_term && !is_sold;
}
