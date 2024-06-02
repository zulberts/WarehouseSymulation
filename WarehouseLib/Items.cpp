#include "Items.h"
#include "Workers.h"
#include <ctime>

// Item class methods
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

// ShipmentDetail struct constructor
ShipmentDetail::ShipmentDetail(const Item& item, int quantity)
    : item(item), quantity(quantity) {}

// Shipment class methods
Shipment::Shipment(const std::vector<ShipmentDetail>& items, const Manager& receivingManager, const Worker& storageWorker, const std::string& deliveryCompany)
    : items(items), receivingManager(receivingManager), storageWorker(storageWorker), deliveryCompany(deliveryCompany) {
    totalcost = 0.0;
    for (const auto& detail : items) {
        totalcost += (detail.item.getPrice() + detail.item.getTax()) * detail.quantity;
    }
}

const std::vector<ShipmentDetail>& Shipment::getProducts() const {
    return items;
}

Manager Shipment::getReceivingManager() const {
    return receivingManager;
}

Worker Shipment::getStorageWorker() const {
    return storageWorker;
}

std::string Shipment::getDeliveryCompany() const {
    return deliveryCompany;
}

double Shipment::getTotalCost() const {
    return totalcost;
}

void Shipment::addProducts(const std::vector<ShipmentDetail>& newItems) {
    std::vector<ShipmentDetail> updatedItems = items;
    updatedItems.insert(updatedItems.end(), newItems.begin(), newItems.end());
    *this = Shipment(updatedItems, receivingManager, storageWorker, deliveryCompany);
}

// Product class methods
Product::Product(const Manager& recManager, const Worker& storWorker, const std::string& name, double price, double tax, const std::string& country, std::time_t validity, int weight, ProductType type)
    : receivingManager(recManager), storageWorker(storWorker), name(name), price(price), tax(tax), country(country), validity_term(validity), weight(weight), type(type), is_sold(false) {
    sale_date = std::time(nullptr);
}

std::time_t Product::getSaleDate() const {
    return sale_date;
}

void Product::setSaleDate(std::time_t newSaleDate) {
    sale_date = newSaleDate;
}

bool Product::isAvailable() const {
    std::time_t currentTime = std::time(nullptr);
    return currentTime < validity_term && !is_sold;
}
