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

ShipmentDetail::ShipmentDetail(const Item& item, int quantity)
    : item(item), quantity(quantity) {}

Product::Product(const Manager& recManager, const Worker& storWorker, const std::string& name, double price, double tax, const Firm& firm, std::time_t expiryDate, int weight, ProductType type, int quantity)
    : Item(name, price, type, tax, expiryDate, weight, firm), receivingManager(recManager), storageWorker(storWorker), quantity(quantity) {}

void Product::updateQuantity(int quantity_sold) {
    quantity -= quantity_sold;
}

int Product::getQuantity() const {
    return quantity;
}
