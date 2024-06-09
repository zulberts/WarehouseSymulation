#include "Shipment.h"
#include <ctime>

Shipment::Shipment(const std::vector<ShipmentDetail>& items, const Manager& receivingManager, const Worker& storageWorker)
    : items(items), receivingManager(receivingManager), storageWorker(storageWorker) {
    totalcost = 0.0;
    for (const auto& detail : items) {
        double itemTotal = detail.item.getPrice() * (1 + detail.item.getTax()) * detail.quantity;
        totalcost += itemTotal;
    }
    std::time_t currentTime = std::time(nullptr);
    deliveryDate = currentTime + 7 * 24 * 60 * 60;
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

double Shipment::getTotalCost() const {
    return totalcost;
}

std::time_t Shipment::getDeliveryDate() const {
    return deliveryDate;
}