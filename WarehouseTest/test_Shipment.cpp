#include "../WarehouseLib/Shipment.h"
#include <gtest/gtest.h>
#include <ctime>

TEST(ShipmentTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item1("Test Item 1", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    Item item2("Test Item 2", 20.0, ProductType::Apparel, 0.2, expiryDate, 300, firm);

    ShipmentDetail detail1(item1, 5);
    ShipmentDetail detail2(item2, 10);

    std::vector<ShipmentDetail> items = { detail1, detail2 };

    Manager receivingManager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker storageWorker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);

    Shipment shipment(items, receivingManager, storageWorker);

    EXPECT_EQ(shipment.getProducts().size(), 2);
    EXPECT_EQ(shipment.getProducts()[0].item.getName(), "Test Item 1");
    EXPECT_EQ(shipment.getProducts()[0].quantity, 5);
    EXPECT_EQ(shipment.getProducts()[1].item.getName(), "Test Item 2");
    EXPECT_EQ(shipment.getProducts()[1].quantity, 10);

    EXPECT_EQ(shipment.getReceivingManager().getName(), "ManagerName");
    EXPECT_EQ(shipment.getReceivingManager().getLastName(), "ManagerLastName");

    EXPECT_EQ(shipment.getStorageWorker().getName(), "WorkerName");
    EXPECT_EQ(shipment.getStorageWorker().getLastName(), "WorkerLastName");

    double expectedTotalCost = (10.0 * 1.1) * 5 + (20.0 * 1.2) * 10;
    EXPECT_DOUBLE_EQ(shipment.getTotalCost(), expectedTotalCost);

    std::time_t currentTime = std::time(nullptr);
    EXPECT_NEAR(shipment.getDeliveryDate(), currentTime + 7 * 24 * 60 * 60, 1);
}

TEST(ShipmentTest, GetProducts) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    ShipmentDetail detail(item, 10);
    std::vector<ShipmentDetail> items = { detail };
    Manager receivingManager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker storageWorker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);

    Shipment shipment(items, receivingManager, storageWorker);

    const auto& products = shipment.getProducts();
    EXPECT_EQ(products.size(), 1);
    EXPECT_EQ(products[0].item.getName(), "Test Item");
    EXPECT_EQ(products[0].quantity, 10);
}

TEST(ShipmentTest, GetReceivingManager) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    ShipmentDetail detail(item, 10);
    std::vector<ShipmentDetail> items = { detail };
    Manager receivingManager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker storageWorker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);

    Shipment shipment(items, receivingManager, storageWorker);

    Manager manager = shipment.getReceivingManager();
    EXPECT_EQ(manager.getName(), "ManagerName");
    EXPECT_EQ(manager.getLastName(), "ManagerLastName");
}

TEST(ShipmentTest, GetStorageWorker) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    ShipmentDetail detail(item, 10);
    std::vector<ShipmentDetail> items = { detail };
    Manager receivingManager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker storageWorker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);

    Shipment shipment(items, receivingManager, storageWorker);

    Worker worker = shipment.getStorageWorker();
    EXPECT_EQ(worker.getName(), "WorkerName");
    EXPECT_EQ(worker.getLastName(), "WorkerLastName");
}

TEST(ShipmentTest, GetTotalCost) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    ShipmentDetail detail(item, 10);
    std::vector<ShipmentDetail> items = { detail };
    Manager receivingManager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker storageWorker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);

    Shipment shipment(items, receivingManager, storageWorker);

    double expectedTotalCost = (10.0 * 1.1) * 10;
    EXPECT_DOUBLE_EQ(shipment.getTotalCost(), expectedTotalCost);
}

TEST(ShipmentTest, GetDeliveryDate) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    ShipmentDetail detail(item, 10);
    std::vector<ShipmentDetail> items = { detail };
    Manager receivingManager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker storageWorker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);

    Shipment shipment(items, receivingManager, storageWorker);

    std::time_t currentTime = std::time(nullptr);
    EXPECT_NEAR(shipment.getDeliveryDate(), currentTime + 7 * 24 * 60 * 60, 1);
}
