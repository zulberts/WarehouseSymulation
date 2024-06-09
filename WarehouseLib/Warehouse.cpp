#include "Warehouse.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

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
        bool found = false;
        for (auto& product : products) {
            if (product->getName() == detail.item.getName() && product->getFirm().getFirmName() == detail.item.getFirm().getFirmName()) {
                product->updateQuantity(detail.quantity);
                found = true;
                break;
            }
        }
        if (!found) {
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

void Warehouse::addTransaction(const std::vector<ShipmentDetail>& items, std::shared_ptr<Customer> customer, const Worker& worker) {
    std::vector<Product> productsToBuy;
    for (const auto& detail : items) {
        for (auto& product : products) {
            if (product->getName() == detail.item.getName() && product->getFirm().getFirmName() == detail.item.getFirm().getFirmName() && product->getQuantity() >= detail.quantity) {
                Product buyingProduct = *product;
                buyingProduct.updateQuantity(detail.quantity);
                productsToBuy.push_back(buyingProduct);
                product->updateQuantity(-detail.quantity);
                break;
            }
        }
    }
    auto transaction = std::make_unique<Transaction>(productsToBuy, worker, customer);
    transactions.push_back(std::move(transaction));
}

void Warehouse::generateDocument(const std::string& path) {
    if (transactions.empty()) {
        std::cerr << "No transactions available to generate a document.\n";
        return;
    }
    size_t index = transactions.size();
    transactions.back()->printDocument(path, static_cast<int>(index));
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

void Warehouse::makePurchase() {
    bool isFirm;
    std::cout << "Are you a firm? (1 for Yes, 0 for No): ";
    std::cin >> isFirm;

    std::shared_ptr<Customer> customer = createCustomer(isFirm);

    if (isFirm) {
        auto firmCustomer = std::dynamic_pointer_cast<FirmCustomer>(customer);
        std::cout << "Welcome, " << firmCustomer->getFirmName() << std::endl;
    }
    else {
        std::cout << "Welcome, " << customer->getName() << std::endl;
    }

    std::map<std::string, int> productSummary;
    for (const auto& product : products) {
        productSummary[product->getName()] += product->getQuantity();
    }

    std::cout << "Available products:\n";
    for (const auto& entry : productSummary) {
        std::cout << "Name: " << entry.first << ", Quantity: " << entry.second << "\n";
    }

    std::string productName;
    int quantity;
    std::cout << "Enter the name of the product you want to buy: ";
    std::cin >> productName;
    std::cout << "Enter the quantity you want to buy: ";
    std::cin >> quantity;

    if (productSummary[productName] < quantity) {
        std::cout << "Product not available or insufficient quantity.\n";
        return;
    }

    std::vector<ShipmentDetail> itemsToBuy;
    int remainingQuantity = quantity;

    for (auto& productPtr : products) {
        if (productPtr->getName() == productName && remainingQuantity > 0) {
            int availableQuantity = productPtr->getQuantity();
            int quantityToBuy = std::min(remainingQuantity, availableQuantity);

            itemsToBuy.push_back(ShipmentDetail(*productPtr, quantityToBuy));

            productPtr->updateQuantity(-quantityToBuy);
            remainingQuantity -= quantityToBuy;
        }
    }

    addTransaction(itemsToBuy, customer, *workers.front());
    generateDocument("./");
}


std::shared_ptr<Customer> Warehouse::createCustomer(bool isFirm) {
    if (isFirm) {
        std::string firmName, firmId, firmCountry;
        std::cout << "Is this a new firm? (1 for Yes, 0 for No): ";
        bool newFirm;
        std::cin >> newFirm;

        if (newFirm) {
            std::cout << "Enter firm name: ";
            std::cin >> firmName;
            std::cout << "Enter firm ID: ";
            std::cin >> firmId;
            std::cout << "Enter firm country: ";
            std::cin >> firmCountry;
            FirmCustomer firmCustomer(firmName, firmId, firmCountry);
            firms.push_back(firmCustomer);
            return std::make_shared<FirmCustomer>(firmCustomer);
        }
        else {
            std::cout << "Enter firm name: ";
            std::cin >> firmName;
            for (const auto& firm : firms) {
                if (firm.getFirmName() == firmName) {
                    return std::make_shared<FirmCustomer>(firm);
                }
            }
            std::cout << "Firm not found.\n";
            return nullptr;
        }
    }
    else {
        std::string name, lastName;
        int age;
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your last name: ";
        std::cin >> lastName;
        std::cout << "Enter your age: ";
        std::cin >> age;
        return std::make_shared<PrivatePerson>(name, lastName, age);
    }
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
        jProduct["quantity"] = product.getQuantity();

        j["products"].push_back(jProduct);
    }

    for (const auto& transaction : transactions) {
        nlohmann::json jTransaction;
        jTransaction["worker"] = { {"name", transaction->getWorker().getName()}, {"lastName", transaction->getWorker().getLastName()} };
        jTransaction["customer"] = { {"name", transaction->getCustomer()->getName()} };
        jTransaction["transactionTime"] = transaction->getTransactionTime();
        jTransaction["canceled"] = transaction->isCanceled();

        for (const auto& product : transaction->getProducts()) {
            nlohmann::json jProduct;

            jProduct["type"] = static_cast<int>(product.getType());
            jProduct["name"] = product.getName();
            jProduct["price"] = product.getPrice();
            jProduct["tax"] = product.getTax();
            jProduct["firm"] = product.getFirm().getFirmName();
            jProduct["expiryDate"] = product.getExpiryDate();
            jProduct["weight"] = product.getWeight();
            jProduct["quantity"] = product.getQuantity();

            jTransaction["products"].push_back(jProduct);
        }

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
            jItem["type"] = static_cast<int>(item.item.getType());

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

    for (const auto& managerPtr : managers) {
        const Manager& manager = *managerPtr;
        nlohmann::json jManager;
        jManager["name"] = manager.getName();
        jManager["lastName"] = manager.getLastName();
        jManager["age"] = manager.getAge();
        jManager["salary"] = manager.getSalary();
        jManager["experience"] = manager.getExperience();

        j["managers"].push_back(jManager);
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
            jProduct["quantity"].get<int>()
        );
        products.push_back(std::move(product));
    }

    for (const auto& jTransaction : j["transactions"]) {
        Worker worker(jTransaction["worker"]["name"], jTransaction["worker"]["lastName"], 0, Post::PhysicalLabor, 0.0, 0);
        std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>(jTransaction["customer"]["name"], "Unknown", 0);

        std::vector<Product> transactionProducts;
        for (const auto& jProduct : jTransaction["products"]) {
            Manager manager("Default", "Manager", 0, 0.0, 0);
            Worker productWorker("Default", "Worker", 0, Post::PhysicalLabor, 0.0, 0);

            Product product(
                manager,
                productWorker,
                jProduct["name"].get<std::string>(),
                jProduct["price"].get<double>(),
                jProduct["tax"].get<double>(),
                Firm(jProduct["firm"].get<std::string>(), "DefaultID", "DefaultCountry"),
                jProduct["expiryDate"].get<std::time_t>(),
                jProduct["weight"].get<int>(),
                static_cast<ProductType>(jProduct["type"].get<int>()),
                jProduct["quantity"].get<int>()
            );
            transactionProducts.push_back(product);
        }

        auto transaction = std::make_unique<Transaction>(
            transactionProducts,
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
                jItem["weight"].get<int>(),
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

    for (const auto& jManager : j["managers"]) {
        auto manager = std::make_unique<Manager>(
            jManager["name"].get<std::string>(),
            jManager["lastName"].get<std::string>(),
            jManager["age"].get<int>(),
            jManager["salary"].get<double>(),
            jManager["experience"].get<int>()
        );
        managers.push_back(std::move(manager));
    }
}

Product* Warehouse::searchByName(const std::string& name) const {
    auto it = std::find_if(products.begin(), products.end(), [&name](const std::unique_ptr<Product>& product) {
        return product->getName() == name;
        });
    return it != products.end() ? it->get() : nullptr;
}

Product* Warehouse::searchByManufacturer(const std::string& manufacturer) const {
    auto it = std::find_if(products.begin(), products.end(), [&manufacturer](const std::unique_ptr<Product>& product) {
        return product->getFirm().getFirmName() == manufacturer;
        });
    return it != products.end() ? it->get() : nullptr;
}

Product* Warehouse::searchByExpiryDate(std::time_t expiryDate) const {
    auto it = std::find_if(products.begin(), products.end(), [expiryDate](const std::unique_ptr<Product>& product) {
        return product->getExpiryDate() == expiryDate;
        });
    return it != products.end() ? it->get() : nullptr;
}

Product* Warehouse::searchByType(ProductType type) const {
    auto it = std::find_if(products.begin(), products.end(), [type](const std::unique_ptr<Product>& product) {
        return product->getType() == type;
        });
    return it != products.end() ? it->get() : nullptr;
}

void Warehouse::addShipmentAsManager(const std::vector<ShipmentDetail>& items, const Manager& manager, const Worker& worker) {
    auto shipment = std::make_unique<Shipment>(items, manager, worker);
    addShipment(std::move(shipment));
}

