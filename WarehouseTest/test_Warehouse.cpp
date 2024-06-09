//#include "../WarehouseLib/Warehouse.h"
//#include <gtest/gtest.h>
//#include <ctime>
//
//TEST(WarehouseTest, AddAndRetrieveShipments) {
//    Warehouse warehouse;
//    std::time_t expiryDate = std::time(nullptr);
//    Firm firm("FirmName", "FirmID", "Country");
//    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
//    ShipmentDetail detail(item, 5);
//    std::vector<ShipmentDetail> items = { detail };
//    Manager receivingManager("ManagerName", "ManagerLastName", 40, 8000, 10);
//    Worker storageWorker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//
//    auto shipment = std::make_unique<Shipment>(items, receivingManager, storageWorker);
//    warehouse.addShipment(std::move(shipment));
//
//    EXPECT_EQ(warehouse.getShipments().size(), 1);
//    EXPECT_EQ(warehouse.getShipments()[0]->getProducts().size(), 1);
//}
//
//TEST(WarehouseTest, AddAndRetrieveWorkers) {
//    Warehouse warehouse;
//    auto worker = std::make_unique<Worker>("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//    warehouse.addWorker(std::move(worker));
//
//    EXPECT_EQ(warehouse.getWorkers().size(), 1);
//    EXPECT_EQ(warehouse.getWorkers()[0]->getName(), "WorkerName");
//}
//
//TEST(WarehouseTest, AddAndRetrieveManagers) {
//    Warehouse warehouse;
//    auto manager = std::make_unique<Manager>("ManagerName", "ManagerLastName", 40, 8000, 10);
//    warehouse.addManager(std::move(manager));
//
//    EXPECT_EQ(warehouse.getManagers().size(), 1);
//    EXPECT_EQ(warehouse.getManagers()[0]->getName(), "ManagerName");
//}
//
//TEST(WarehouseTest, AddAndRetrieveTransactions) {
//    Warehouse warehouse;
//    std::time_t expiryDate = std::time(nullptr);
//    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
//    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//    Firm firm("FirmName", "FirmID", "Country");
//    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);
//
//    std::vector<Product> products = { product };
//    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);
//
//    auto transaction = std::make_unique<Transaction>(products, worker, customer);
//    warehouse.addTransaction(std::move(transaction));
//
//    EXPECT_EQ(warehouse.getTransactions().size(), 1);
//    EXPECT_EQ(warehouse.getTransactions()[0]->getProducts().size(), 1);
//}
//
//TEST(WarehouseTest, FireWorker) {
//    Warehouse warehouse;
//    auto worker = std::make_unique<Worker>("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//    warehouse.addWorker(std::move(worker));
//
//    EXPECT_EQ(warehouse.getWorkers().size(), 1);
//    EXPECT_TRUE(warehouse.fireWorker(1));
//    EXPECT_EQ(warehouse.getWorkers().size(), 0);
//}
//
//TEST(WarehouseTest, SearchByName) {
//    Warehouse warehouse;
//    std::time_t expiryDate = std::time(nullptr);
//    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
//    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//    Firm firm("FirmName", "FirmID", "Country");
//    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);
//
//    auto productPtr = std::make_unique<Product>(product);
//    warehouse.addShipment(std::make_unique<Shipment>(std::vector<ShipmentDetail>{ShipmentDetail(*productPtr, 5)}, manager, worker));
//
//    try {
//        auto result = warehouse.searchByName("Product");
//        EXPECT_EQ(result.getName(), "Product");
//    }
//    catch (const std::runtime_error& e) {
//        FAIL() << "Product not found: " << e.what();
//    }
//}
//
//TEST(WarehouseTest, SearchByManufacturer) {
//    Warehouse warehouse;
//    std::time_t expiryDate = std::time(nullptr);
//    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
//    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//    Firm firm("FirmName", "FirmID", "Country");
//    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);
//
//    auto productPtr = std::make_unique<Product>(product);
//    warehouse.addShipment(std::make_unique<Shipment>(std::vector<ShipmentDetail>{ShipmentDetail(*productPtr, 5)}, manager, worker));
//
//    try {
//        auto result = warehouse.searchByManufacturer("FirmName");
//        EXPECT_EQ(result.getFirm().getFirmName(), "FirmName");
//    }
//    catch (const std::runtime_error& e) {
//        FAIL() << "Product not found: " << e.what();
//    }
//}
//
//TEST(WarehouseTest, SearchByExpiryDate) {
//    Warehouse warehouse;
//    std::time_t expiryDate = std::time(nullptr);
//    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
//    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//    Firm firm("FirmName", "FirmID", "Country");
//    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);
//
//    auto productPtr = std::make_unique<Product>(product);
//    warehouse.addShipment(std::make_unique<Shipment>(std::vector<ShipmentDetail>{ShipmentDetail(*productPtr, 5)}, manager, worker));
//
//    try {
//        auto result = warehouse.searchByExpiryDate(expiryDate);
//        EXPECT_EQ(result.getExpiryDate(), expiryDate);
//    }
//    catch (const std::runtime_error& e) {
//        FAIL() << "Product not found: " << e.what();
//    }
//}
//
//TEST(WarehouseTest, SearchByType) {
//    Warehouse warehouse;
//    std::time_t expiryDate = std::time(nullptr);
//    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
//    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
//    Firm firm("FirmName", "FirmID", "Country");
//    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);
//
//    auto productPtr = std::make_unique<Product>(product);
//    warehouse.addShipment(std::make_unique<Shipment>(std::vector<ShipmentDetail>{ShipmentDetail(*productPtr, 5)}, manager, worker));
//
//    try {
//        auto result = warehouse.searchByType(ProductType::Electronics);
//        EXPECT_EQ(result.getType(), ProductType::Electronics);
//    }
//    catch (const std::runtime_error& e) {
//        FAIL() << "Product not found: " << e.what();
//    }
//}