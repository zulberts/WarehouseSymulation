#include "Warehouse.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

Warehouse::Warehouse() {}

const std::vector<std::unique_ptr<Product>>& Warehouse::getProducts() const {
    return products;
}

const std::vector<std::unique_ptr<Shipment>>& Warehouse::getShipments() const {
    return shipments;
}

const std::vector<std::unique_ptr<Worker>>& Warehouse::getWorkers() const {
    return workers;
}

const std::vector<std::unique_ptr<Manager>>& Warehouse::getManagers() const {
    return managers;
}

const std::vector<std::unique_ptr<Transaction>>& Warehouse::getTransactions() const {
    return transactions;
}

void Warehouse::addShipment(std::unique_ptr<Shipment> shipment) {
    for (const auto& detail : shipment->getProducts()) {
        for (int i = 0; i < detail.quantity; ++i) {
            auto product = std::make_unique<Product>(
                shipment->getReceivingManager(),
                shipment->getStorageWorker(),
                detail.item.getName(),
                detail.item.getPrice(),
                detail.item.getTax(),
                detail.item.getFirm(),
                detail.item.getExpiryDate(),
                detail.item.getWeight(),
                detail.item.getType(),
                detail.quantity
            );
            products.push_back(std::move(product));
        }
    }
    shipments.push_back(std::move(shipment));
}

void Warehouse::addWorker(std::unique_ptr<Worker> worker) {
    workers.push_back(std::move(worker));
}

void Warehouse::addManager(std::unique_ptr<Manager> manager) {
    managers.push_back(std::move(manager));
}

void Warehouse::addTransaction(std::unique_ptr<Transaction> transaction) {
    transactions.push_back(std::move(transaction));
}

std::vector<Product*> Warehouse::searchByName(const std::string& name) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->getName() == name) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByManufacturer(const std::string& manufacturer) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->getFirm().getFirmName() == manufacturer) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByExpiryDate(std::time_t expiryDate) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->getExpiryDate() == expiryDate) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByType(ProductType type) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->getType() == type) {
            result.push_back(product.get());
        }
    }
    return result;
}

void Warehouse::generateInvoice(const std::string& path) {
    if (transactions.empty()) {
        std::cerr << "No transactions available to generate an invoice.\n";
        return;
    }
    int index = transactions.size(); // Example index, can be changed based on your requirements
    transactions.back()->printDocument(path, index);
}

void Warehouse::generateReceipt(const std::string& path) {
    if (transactions.empty()) {
        std::cerr << "No transactions available to generate a receipt.\n";
        return;
    }
    int index = transactions.size(); // Example index, can be changed based on your requirements
    transactions.back()->printDocument(path, index);
}

void Warehouse::saveToJson(const std::string& filename) const {
    nlohmann::json j;

    for (const auto& productPtr : products) {
        const Product& product = *productPtr;
        nlohmann::json jProduct;

        jProduct["type"] = static_cast<int>(product.getType());
        jProduct["name"] = product.getName();
        jProduct["price"] = product.getPrice();
        jProduct["tax"] = product.getTax();
        jProduct["firm"] = product.getFirm().getFirmName();
        jProduct["expiryDate"] = product.getExpiryDate();
        jProduct["weight"] = product.getWeight();

        j["products"].push_back(jProduct);
    }

    for (const auto& transaction : transactions) {
        nlohmann::json jTransaction;
        jTransaction["worker"] = { {"name", transaction->getWorker().getName()}, {"lastName", transaction->getWorker().getLastName()} };
        jTransaction["customer"] = { {"name", transaction->getCustomer()->getName()} };
        jTransaction["transactionTime"] = transaction->getTransactionTime();
        jTransaction["canceled"] = transaction->isCanceled();

        j["transactions"].push_back(jTransaction);
    }

    for (const auto& shipmentPtr : shipments) {
        const Shipment& shipment = *shipmentPtr;
        nlohmann::json jShipment;
        jShipment["receivingManager"] = { {"name", shipment.getReceivingManager().getName()}, {"lastName", shipment.getReceivingManager().getLastName()} };
        jShipment["storageWorker"] = { {"name", shipment.getStorageWorker().getName()}, {"lastName", shipment.getStorageWorker().getLastName()} };
        jShipment["totalcost"] = shipment.getTotalCost();
        jShipment["deliveryDate"] = shipment.getDeliveryDate();

        for (const auto& item : shipment.getProducts()) {
            nlohmann::json jItem;
            jItem["name"] = item.item.getName();
            jItem["price"] = item.item.getPrice();
            jItem["tax"] = item.item.getTax();
            jItem["expiryDate"] = item.item.getExpiryDate();
            jItem["quantity"] = item.quantity;

            jShipment["items"].push_back(jItem);
        }

        j["shipments"].push_back(jShipment);
    }

    for (const auto& workerPtr : workers) {
        const Worker& worker = *workerPtr;
        nlohmann::json jWorker;
        jWorker["name"] = worker.getName();
        jWorker["lastName"] = worker.getLastName();
        jWorker["age"] = worker.getAge();
        jWorker["post"] = static_cast<int>(worker.getPost());
        jWorker["salary"] = worker.getSalary();
        jWorker["experience"] = worker.getExperience();

        j["workers"].push_back(jWorker);
    }

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
    else {
        throw std::runtime_error("Unable to open file for writing");
    }
}

void Warehouse::loadFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for reading");
    }

    nlohmann::json j;
    file >> j;
    file.close();

    for (const auto& jProduct : j["products"]) {
        Manager manager("Default", "Manager", 0, 0.0, 0);
        Worker worker("Default", "Worker", 0, Post::PhysicalLabor, 0.0, 0);

        auto product = std::make_unique<Product>(
            manager,
            worker,
            jProduct["name"].get<std::string>(),
            jProduct["price"].get<double>(),
            jProduct["tax"].get<double>(),
            Firm(jProduct["firm"].get<std::string>(), "DefaultID", "DefaultCountry"),
            jProduct["expiryDate"].get<std::time_t>(),
            jProduct["weight"].get<int>(),
            static_cast<ProductType>(jProduct["type"].get<int>()),
            0
        );
        products.push_back(std::move(product));
    }

    for (const auto& jTransaction : j["transactions"]) {
        Worker worker(jTransaction["worker"]["name"], jTransaction["worker"]["lastName"], 0, Post::PhysicalLabor, 0.0, 0);
        std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>(jTransaction["customer"]["name"], "Unknown", 0);

        auto transaction = std::make_unique<Transaction>(
            std::vector<Product>{},
            worker,
            customer
        );
        if (jTransaction["canceled"].get<bool>()) {
            transaction->cancel();
        }
        transactions.push_back(std::move(transaction));
    }

    for (const auto& jShipment : j["shipments"]) {
        Manager receivingManager(jShipment["receivingManager"]["name"], jShipment["receivingManager"]["lastName"], 0, 0.0, 0);
        Worker storageWorker(jShipment["storageWorker"]["name"], jShipment["storageWorker"]["lastName"], 0, Post::PhysicalLabor, 0.0, 0);

        std::vector<ShipmentDetail> items;
        for (const auto& jItem : jShipment["items"]) {
            Item item(
                jItem["name"].get<std::string>(),
                jItem["price"].get<double>(),
                static_cast<ProductType>(jItem["type"].get<int>()),
                jItem["tax"].get<double>(),
                jItem["expiryDate"].get<std::time_t>(),
                0,
                Firm("DefaultFirm", "DefaultID", "DefaultCountry")
            );
            int quantity = jItem["quantity"];
            items.emplace_back(ShipmentDetail(item, quantity));
        }

        auto shipment = std::make_unique<Shipment>(
            items,
            receivingManager,
            storageWorker
        );
        shipments.push_back(std::move(shipment));
    }

    for (const auto& jWorker : j["workers"]) {
        auto worker = std::make_unique<Worker>(
            jWorker["name"].get<std::string>(),
            jWorker["lastName"].get<std::string>(),
            jWorker["age"].get<int>(),
            static_cast<Post>(jWorker["post"].get<int>()),
            jWorker["salary"].get<double>(),
            jWorker["experience"].get<int>()
        );
        workers.push_back(std::move(worker));
    }
}

void Warehouse::listWorkers() const {
    for (size_t i = 0; i < workers.size(); ++i) {
        std::cout << i + 1 << ". " << workers[i]->getName() << " " << workers[i]->getLastName() << "\n";
    }
}

bool Warehouse::fireWorker(size_t index) {
    if (index < 1 || index > workers.size()) {
        std::cerr << "Invalid worker index.\n";
        return false;
    }
    workers.erase(workers.begin() + index - 1);
    return true;
}
