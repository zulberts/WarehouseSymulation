#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include "Items.h"
#include "Workers.h"
#include "Customers.h"

//DONE

class Shipment {
private:
    std::vector<ShipmentDetail> items;
    Manager receivingManager;
    Worker storageWorker;
    std::string deliveryCompany;
    double totalcost;
    std::time_t deliveryDate;

public:
    Shipment(const std::vector<ShipmentDetail>& items, const Manager& receivingManager, const Worker& storageWorker, const std::string& deliveryCompany, std::time_t deliveryDate);

    const std::vector<ShipmentDetail>& getProducts() const;
    Manager getReceivingManager() const;
    Worker getStorageWorker() const;
    std::string getDeliveryCompany() const;
    double getTotalCost() const;
    std::time_t getDeliveryDate() const;
    void addShipmentDetail(const std::vector<ShipmentDetail>& newItems);
};

