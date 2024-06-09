#include "../WarehouseLib/Items.h"
#include <gtest/gtest.h>
#include <ctime>

TEST(ItemTest, Constructor) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);

    EXPECT_EQ(item.getName(), "Test Item");
    EXPECT_EQ(item.getPrice(), 10.0);
    EXPECT_EQ(item.getType(), ProductType::Electronics);
    EXPECT_EQ(item.getTax(), 0.1);
    EXPECT_EQ(item.getExpiryDate(), expiryDate);
    EXPECT_EQ(item.getWeight(), 500);
    EXPECT_EQ(item.getFirm().getFirmName(), "FirmName");
}

TEST(ItemTest, GetName) {
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, std::time(nullptr), 500, firm);
    EXPECT_EQ(item.getName(), "Test Item");
}

TEST(ItemTest, GetPrice) {
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, std::time(nullptr), 500, firm);
    EXPECT_EQ(item.getPrice(), 10.0);
}

TEST(ItemTest, GetType) {
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, std::time(nullptr), 500, firm);
    EXPECT_EQ(item.getType(), ProductType::Electronics);
}

TEST(ItemTest, GetTax) {
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, std::time(nullptr), 500, firm);
    EXPECT_EQ(item.getTax(), 0.1);
}

TEST(ItemTest, GetExpiryDate) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    EXPECT_EQ(item.getExpiryDate(), expiryDate);
}

TEST(ItemTest, GetWeight) {
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, std::time(nullptr), 500, firm);
    EXPECT_EQ(item.getWeight(), 500);
}

TEST(ItemTest, GetFirm) {
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, std::time(nullptr), 500, firm);
    EXPECT_EQ(item.getFirm().getFirmName(), "FirmName");
    EXPECT_EQ(item.getFirm().getId(), "FirmID");
    EXPECT_EQ(item.getFirm().getCountry(), "Country");
}

TEST(ShipmentDetailTest, Constructor) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    ShipmentDetail shipmentDetail(item, 10);

    EXPECT_EQ(shipmentDetail.item.getName(), "Test Item");
    EXPECT_EQ(shipmentDetail.quantity, 10);
}

TEST(ProductTest, Constructor) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Test Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    EXPECT_EQ(product.getName(), "Test Product");
    EXPECT_EQ(product.getPrice(), 20.0);
    EXPECT_EQ(product.getTax(), 0.2);
    EXPECT_EQ(product.getExpiryDate(), expiryDate);
    EXPECT_EQ(product.getWeight(), 1000);
    EXPECT_EQ(product.getType(), ProductType::Electronics);
    EXPECT_EQ(product.getFirm().getFirmName(), "FirmName");
    EXPECT_EQ(product.getQuantity(), 50);
}

TEST(ProductTest, UpdateQuantity) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Test Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    product.updateQuantity(10);
    EXPECT_EQ(product.getQuantity(), 40);
}

TEST(ProductTest, GetQuantity) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Test Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    EXPECT_EQ(product.getQuantity(), 50);
}
