#include "Shipment.h"

//DONE

Shipment::Shipment(const std::vector<ShipmentDetail>& items, const Manager& receivingManager, const Worker& storageWorker, const std::string& deliveryCompany, std::time_t deliveryDate)
    : items(items), receivingManager(receivingManager), storageWorker(storageWorker), deliveryCompany(deliveryCompany), deliveryDate(deliveryDate) {
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

std::time_t Shipment::getDeliveryDate() const {
    return deliveryDate;
}

void Shipment::addShipmentDetail(const std::vector<ShipmentDetail>& newItems) {
    std::vector<ShipmentDetail> updatedItems = items;
    updatedItems.insert(updatedItems.end(), newItems.begin(), newItems.end());
    *this = Shipment(updatedItems, receivingManager, storageWorker, deliveryCompany, deliveryDate);
}
