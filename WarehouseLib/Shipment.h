#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include "Items.h"
#include "Workers.h"
#include "Customers.h"

class Shipment {
private:
    std::vector<ShipmentDetail> items;
    Manager receivingManager;
    Worker storageWorker;
    double totalcost;
    std::time_t deliveryDate;

public:
    Shipment(const std::vector<ShipmentDetail>& items, const Manager& receivingManager, const Worker& storageWorker);

    const std::vector<ShipmentDetail>& getProducts() const;
    Manager getReceivingManager() const;
    Worker getStorageWorker() const;
    double getTotalCost() const;
    std::time_t getDeliveryDate() const;

};

