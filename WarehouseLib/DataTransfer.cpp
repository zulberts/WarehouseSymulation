#include "DataTransfer.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "Items.h"

//DONE

void DataTransfer::saveToJson(const Warehouse& warehouse, const std::string& filename) {
    nlohmann::json j;

    for (const auto& productPtr : warehouse.getProducts()) {
        const Product& product = *productPtr;
        nlohmann::json jProduct;

        jProduct["type"] = static_cast<int>(product.type);
        jProduct["name"] = product.name;
        jProduct["price"] = product.price;
        jProduct["tax"] = product.tax;
        jProduct["country"] = product.country;
        jProduct["validity_term"] = product.validity_term;
        jProduct["weight"] = product.weight;
        jProduct["sale_date"] = product.getSaleDate();
        jProduct["is_sold"] = !product.isAvailable();

        j["products"].push_back(jProduct);
    }

    for (const auto& transaction : warehouse.getTransactions()) {
        nlohmann::json jTransaction;
        jTransaction["product_name"] = transaction->getProduct().name;
        jTransaction["quantity"] = transaction->getQuantity();
        jTransaction["summaryPrice"] = transaction->getSummaryPrice();
        jTransaction["worker"] = { {"name", transaction->getWorker().getName()}, {"lastName", transaction->getWorker().getLastName()} };
        jTransaction["customer"] = { {"name", transaction->getCustomer()->getName()}, {"lastName", transaction->getCustomer()->getLastName()} };
        jTransaction["transactionTime"] = transaction->getTransactionTime();
        jTransaction["canceled"] = transaction->isCanceled();

        j["transactions"].push_back(jTransaction);
    }

    for (const auto& shipmentPtr : warehouse.getShipments()) {
        const Shipment& shipment = *shipmentPtr;
        nlohmann::json jShipment;

        jShipment["receivingManager"] = { {"name", shipment.getReceivingManager().getName()}, {"lastName", shipment.getReceivingManager().getLastName()} };
        jShipment["storageWorker"] = { {"name", shipment.getStorageWorker().getName()}, {"lastName", shipment.getStorageWorker().getLastName()} };
        jShipment["deliveryCompany"] = shipment.getDeliveryCompany();
        jShipment["totalcost"] = shipment.getTotalCost();
        jShipment["deliveryDate"] = shipment.getDeliveryDate();
        jShipment["customer"] = { {"name", shipment.getCustomer()->getName()}, {"lastName", shipment.getCustomer()->getLastName()} };

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

    for (const auto& workerPtr : warehouse.getWorkers()) {
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

Warehouse DataTransfer::loadFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for reading");
    }

    nlohmann::json j;
    file >> j;
    file.close();

    Warehouse warehouse;

    for (const auto& jProduct : j["products"]) {
        Manager manager("Default", "Manager", 0, 0.0, 0);
        Worker worker("Default", "Worker", 0, Post::PhysicalLabor, 0.0, 0);

        Product product(
            manager,
            worker,
            jProduct["name"].get<std::string>(),
            jProduct["price"].get<double>(),
            jProduct["tax"].get<double>(),
            jProduct["country"].get<std::string>(),
            jProduct["validity_term"].get<std::time_t>(),
            jProduct["weight"].get<int>(),
            static_cast<ProductType>(jProduct["type"].get<int>())
        );

        product.setSaleDate(jProduct["sale_date"].get<std::time_t>());
        warehouse.addProduct(std::make_unique<Product>(product));
    }

    for (const auto& jTransaction : j["transactions"]) {
        Manager manager("Default", "Manager", 0, 0.0, 0);
        Worker worker(jTransaction["worker"]["name"], jTransaction["worker"]["lastName"], 0, Post::PhysicalLabor, 0.0, 0);

        std::shared_ptr<Customer> customer;
        if (jTransaction["customer"]["lastName"] == "Firm") {
            customer = std::make_shared<Firm>(jTransaction["customer"]["name"], jTransaction["customer"]["lastName"], 0, "", "", "");
        }
        else {
            customer = std::make_shared<PrivatePerson>(jTransaction["customer"]["name"], jTransaction["customer"]["lastName"], 0);
        }

        auto products = warehouse.searchByName(jTransaction["product_name"].get<std::string>());
        if (products.empty()) {
            throw std::runtime_error("Product not found in warehouse");
        }
        Product product = *products.front();

        auto transaction = std::make_unique<Transaction>(
            product,
            jTransaction["quantity"].get<int>(),
            jTransaction["summaryPrice"].get<double>(),
            worker,
            customer
        );

        if (jTransaction["canceled"].get<bool>()) {
            transaction->cancel();
        }

        warehouse.addTransaction(std::move(transaction));
    }

    for (const auto& jShipment : j["shipments"]) {
        Manager receivingManager(jShipment["receivingManager"]["name"], jShipment["receivingManager"]["lastName"], 0, 0.0, 0);
        Worker storageWorker(jShipment["storageWorker"]["name"], jShipment["storageWorker"]["lastName"], 0, Post::PhysicalLabor, 0.0, 0);
        std::string deliveryCompany = jShipment["deliveryCompany"];
        double totalcost = jShipment["totalcost"];
        std::time_t deliveryDate = jShipment["deliveryDate"];

        std::vector<ShipmentDetail> items;
        for (const auto& jItem : jShipment["items"]) {
            Item item(
                jItem["name"].get<std::string>(),
                jItem["price"].get<double>(),
                static_cast<ProductType>(jItem["type"].get<int>()),
                jItem["tax"].get<double>(),
                jItem["expiryDate"].get<std::time_t>()
            );
            int quantity = jItem["quantity"];
            items.emplace_back(ShipmentDetail(item, quantity, deliveryDate));
        }

        std::shared_ptr<Customer> customer;
        if (jShipment["customer"]["lastName"] == "Firm") {
            customer = std::make_shared<Firm>(jShipment["customer"]["name"], jShipment["customer"]["lastName"], 0, "", "", "");
        }
        else {
            customer = std::make_shared<PrivatePerson>(jShipment["customer"]["name"], jShipment["customer"]["lastName"], 0);
        }

        auto shipment = std::make_unique<Shipment>(items, receivingManager, storageWorker, deliveryCompany, deliveryDate, customer);
        warehouse.addShipment(std::move(shipment));
    }

    for (const auto& jWorker : j["workers"]) {
        Worker worker(
            jWorker["name"].get<std::string>(),
            jWorker["lastName"].get<std::string>(),
            jWorker["age"].get<int>(),
            static_cast<Post>(jWorker["post"].get<int>()),
            jWorker["salary"].get<double>(),
            jWorker["experience"].get<int>()
        );

        warehouse.addWorker(std::make_unique<Worker>(worker));
    }

    return warehouse;
}
