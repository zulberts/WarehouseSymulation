#include "Warehouse.h"
#include <nlohmann/json.hpp>

//DONE

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    products.push_back(std::move(product));
}

const std::vector<std::unique_ptr<Product>>& Warehouse::getProducts() const {
    return products;
}

std::vector<Product*> Warehouse::searchByName(const std::string& name) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->name == name) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByManufacturer(const std::string& manufacturer) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->country == manufacturer) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByExpiryDate(std::time_t expiryDate) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->validity_term == expiryDate) {
            result.push_back(product.get());
        }
    }
    return result;
}

std::vector<Product*> Warehouse::searchByType(ProductType type) const {
    std::vector<Product*> result;
    for (const auto& product : products) {
        if (product->type == type) {
            result.push_back(product.get());
        }
    }
    return result;
}

void Warehouse::addTransaction(std::unique_ptr<Transaction> transaction) {
    transactionRegister.addTransaction(std::move(transaction));
}

const std::vector<std::unique_ptr<Transaction>>& Warehouse::getTransactions() const {
    return transactionRegister.getTransactions();
}

void Warehouse::addWorker(std::unique_ptr<Worker> worker) {
    workers.push_back(std::move(worker));
}

const std::vector<std::unique_ptr<Worker>>& Warehouse::getWorkers() const {
    return workers;
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
                "Unknown",
                detail.item.getExpiryDate(),
                1,
                detail.item.getType()
            );
            addProduct(std::move(product));
        }
    }
    shipments.push_back(std::move(shipment));
}

const std::vector<std::unique_ptr<Shipment>>& Warehouse::getShipments() const {
    return shipments;
}

void Warehouse::applyDiscounts(double discountRate, std::time_t daysBeforeExpiry) {
    std::time_t currentTime = std::time(nullptr);
    for (auto& product : products) {
        if (std::difftime(product->validity_term, currentTime) <= daysBeforeExpiry * 24 * 60 * 60) {
            product->price -= product->price * discountRate;
        }
    }
}

void Warehouse::generateInvoice(const std::string& invoiceNumber, const Person& seller, std::shared_ptr<Customer> customer, const std::string& path, const std::vector<Transaction*>& transactions) {
    if (std::dynamic_pointer_cast<Firm>(customer)) {
        std::vector<ShipmentDetail> products;
        for (const auto& transaction : transactions) {
            products.emplace_back(ShipmentDetail(Item(transaction->getProduct().name, transaction->getProduct().price, transaction->getProduct().type, transaction->getProduct().tax, transaction->getProduct().validity_term), transaction->getQuantity(), transaction->getTransactionTime()));
        }
        Invoice invoice(invoiceNumber, seller, customer);
        invoice.GenerateDocument(products, path);
    }
    else {
        throw std::invalid_argument("Customer is not eligible for an invoice.");
    }
}

void Warehouse::generateReceipt(const std::string& paymentMethod, std::shared_ptr<Customer> customer, const std::string& path, const std::vector<Transaction*>& transactions) {
    if (std::dynamic_pointer_cast<PrivatePerson>(customer)) {
        std::vector<ShipmentDetail> products;
        for (const auto& transaction : transactions) {
            products.emplace_back(ShipmentDetail(Item(transaction->getProduct().name, transaction->getProduct().price, transaction->getProduct().type, transaction->getProduct().tax, transaction->getProduct().validity_term), transaction->getQuantity(), transaction->getTransactionTime()));
        }
        Receipt receipt(paymentMethod, customer);
        receipt.GenerateDocument(products, path);
    }
    else {
        throw std::invalid_argument("Customer is not eligible for a receipt.");
    }
}


void Warehouse::saveToJson(const std::string& filename) const {
    nlohmann::json j;

    for (const auto& productPtr : products) {
        const Product& product = *productPtr;
        nlohmann::json jProduct;

        jProduct["type"] = static_cast<int>(product.type);
        jProduct["name"] = product.name;
        jProduct["price"] = product.price;
        jProduct["tax"] = product.tax;
        jProduct["country"] = "Unknown";
        jProduct["validity_term"] = product.validity_term;
        jProduct["weight"] = product.weight;
        jProduct["sale_date"] = product.getSaleDate();
        jProduct["is_sold"] = !product.isAvailable();

        j["products"].push_back(jProduct);
    }

    for (const auto& transaction : transactionRegister.getTransactions()) {
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

    for (const auto& shipmentPtr : shipments) {
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

        Product product(
            manager,
            worker,
            jProduct["name"].get<std::string>(),
            jProduct["price"].get<double>(),
            jProduct["tax"].get<double>(),
            "Unknown",
            jProduct["validity_term"].get<std::time_t>(),
            jProduct["weight"].get<int>(),
            static_cast<ProductType>(jProduct["type"].get<int>())
        );
        product.setSaleDate(jProduct["sale_date"].get<std::time_t>());
        this->addProduct(std::make_unique<Product>(product));
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

        auto products = this->searchByName(jTransaction["product_name"].get<std::string>());
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

        this->addTransaction(std::move(transaction));
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
        this->addShipment(std::move(shipment));
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

        this->addWorker(std::make_unique<Worker>(worker));
    }
}

void Warehouse::listWorkers() const {
    for (size_t i = 0; i < workers.size(); ++i) {
        std::cout << i + 1 << ". " << workers[i]->getName() << " " << workers[i]->getLastName() << std::endl;
    }
}

bool Warehouse::fireWorker(size_t index) {
    if (index < 1 || index > workers.size()) {
        std::cerr << "Invalid worker index." << std::endl;
        return false;
    }
    workers.erase(workers.begin() + index - 1);
    return true;
}