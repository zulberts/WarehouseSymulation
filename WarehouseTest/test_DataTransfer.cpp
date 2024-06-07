#include <gtest/gtest.h>
#include "../WarehouseLib/DataTransfer.h"
#include "../WarehouseLib/Warehouse.h"
#include "../WarehouseLib/Items.h"
#include "../WarehouseLib/Workers.h"
#include "../WarehouseLib/Customers.h"
#include <fstream>

TEST(DataTransferTest, SaveAndLoadWarehouse) {
    Warehouse warehouse;

    Manager manager("Andrzej", "Duda", 45, 6000, 10);
    auto worker1 = std::make_unique<Worker>("Donald", "Tusk", 30, Post::PhysicalLabor, 3000, 5);
    auto worker2 = std::make_unique<Worker>("Jaroslaw", "Kaczynski", 50, Post::WarehouseManagement, 5000, 20);
    Worker* rawWorker2 = worker2.get();
    warehouse.addWorker(std::move(worker1));
    warehouse.addWorker(std::move(worker2));

    auto product1 = std::make_unique<Product>(manager, *rawWorker2, "Apple", 1.0, 0.1, "USA", std::time(nullptr) + 86400, 100, ProductType::Perishable);
    auto product2 = std::make_unique<Product>(manager, *rawWorker2, "Laptop", 1000.0, 0.2, "China", std::time(nullptr) + 86400 * 30, 2000, ProductType::Electronics);
    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));

    auto customer = std::make_shared<PrivatePerson>("Donald", "Tusk", 30);

    Product productCopy = *warehouse.searchByName("Apple").front();
    auto transaction = std::make_unique<Transaction>(productCopy, 5, 5.0, *rawWorker2, customer);
    warehouse.addTransaction(std::move(transaction));

    std::vector<ShipmentDetail> items;
    Item item(productCopy.name, productCopy.price, productCopy.type, productCopy.tax, productCopy.validity_term);
    items.emplace_back(item, 5, std::time(nullptr) + 86400);
    auto shipment = std::make_unique<Shipment>(items, manager, *rawWorker2, "DHL", std::time(nullptr) + 86400, customer);
    warehouse.addShipment(std::move(shipment));

    DataTransfer::saveToJson(warehouse, "warehouse_test.json");

    Warehouse loadedWarehouse = DataTransfer::loadFromJson("warehouse_test.json");

    const auto& loadedProducts = loadedWarehouse.getProducts();
    ASSERT_EQ(loadedProducts.size(), 2);
    EXPECT_EQ(loadedProducts[0]->name, "Apple");
    EXPECT_EQ(loadedProducts[1]->name, "Laptop");

    const auto& loadedTransactions = loadedWarehouse.getTransactions();
    ASSERT_EQ(loadedTransactions.size(), 1);
    EXPECT_EQ(loadedTransactions[0]->getProduct().name, "Apple");
    EXPECT_EQ(loadedTransactions[0]->getQuantity(), 5);

    const auto& loadedShipments = loadedWarehouse.getShipments();
    ASSERT_EQ(loadedShipments.size(), 1);
    EXPECT_EQ(loadedShipments[0]->getDeliveryCompany(), "DHL");
    EXPECT_EQ(loadedShipments[0]->getProducts()[0].item.getName(), "Apple");

    const auto& loadedWorkers = loadedWarehouse.getWorkers();
    ASSERT_EQ(loadedWorkers.size(), 2);
    EXPECT_EQ(loadedWorkers[0]->getName(), "Donald");
    EXPECT_EQ(loadedWorkers[1]->getName(), "Jaroslaw");
}
