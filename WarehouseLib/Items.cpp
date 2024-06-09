#include "Items.h"
#include "Workers.h"
#include <ctime>

Item::Item(const std::string& name, double price, const ProductType type, double tax, std::time_t expiryDate, int weight, const Firm& firm)
    : name(name), price(price), type(type), tax(tax), expiryDate(expiryDate), weight(weight), firm(firm) {}

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

int Item::getWeight() const {
    return weight;
}

Firm Item::getFirm() const {
    return firm;
}

ShipmentDetail::ShipmentDetail(const Item& item, int quantity, std::time_t arrivalDate)
    : item(item), quantity(quantity), arrivalDate(arrivalDate) {}

Product::Product(const Manager& recManager, const Worker& storWorker, const std::string& name, double price, double tax, const Firm& firm, std::time_t expiryDate, int weight, ProductType type)
    : Item(name, price, type, tax, expiryDate, weight, firm), receivingManager(recManager), storageWorker(storWorker), isSold(false), saleDate(0) {}

std::time_t Product::getSaleDate() const {
    return saleDate;
}

bool Product::getIsSold() const{

    return isSold;
}

void Product::setSaleDate(std::time_t newSaleDate) {
    saleDate = newSaleDate;
    this->isSold = !(this->isSold);
}

//bool Product::isAvailable() const {
//    std::time_t currentTime = std::time(nullptr);
//    return currentTime < getExpiryDate() && !isSold;
//}