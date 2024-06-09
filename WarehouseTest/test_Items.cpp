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

TEST(ShipmentDetailTest, Constructor) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Test Item", 10.0, ProductType::Electronics, 0.1, expiryDate, 500, firm);
    ShipmentDetail shipmentDetail(item, 10);

    EXPECT_EQ(shipmentDetail.item.getFirm().getFirmName(), "FirmName");
    EXPECT_EQ(shipmentDetail.quantity, 10);
}

TEST(ProductTest, Constructor) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("Grzegorz", "Król", 50, 8000.0, 25);
    Worker worker("Franciszek", "Zielony", 45, Post::PhysicalLabor, 4000.0, 20);
    worker.addOpinion("Doswiadczony");
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Test Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 10);

    EXPECT_EQ(product.getName(), "Test Product");
    EXPECT_EQ(product.getPrice(), 20.0);
    EXPECT_EQ(product.getTax(), 0.2);
    EXPECT_EQ(product.getExpiryDate(), expiryDate);
    EXPECT_EQ(product.getWeight(), 1000);
    EXPECT_EQ(product.getType(), ProductType::Electronics);
    EXPECT_EQ(product.getFirm().getFirmName(), "FirmName");
}

TEST(ItemTest, GetPrice) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Orange", 2.0, ProductType::Perishable, 0.15, expiryDate, 200, firm);
    EXPECT_DOUBLE_EQ(item.getPrice(), 2.0);
}

TEST(ItemTest, GetTax) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Shirt", 50.0, ProductType::Apparel, 0.05, expiryDate, 500, firm);
    EXPECT_DOUBLE_EQ(item.getTax(), 0.05);
}

TEST(ItemTest, GetExpiryDate) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Milk", 3.0, ProductType::Perishable, 0.1, expiryDate, 1000, firm);
    EXPECT_EQ(item.getExpiryDate(), expiryDate);
}

TEST(ItemTest, GetWeight) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Watermelon", 5.0, ProductType::Perishable, 0.2, expiryDate, 2000, firm);
    EXPECT_EQ(item.getWeight(), 2000);
}

TEST(ItemTest, GetFirm) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Grapes", 4.0, ProductType::Perishable, 0.15, expiryDate, 500, firm);
    EXPECT_EQ(item.getFirm().getFirmName(), "FirmName");
    EXPECT_EQ(item.getFirm().getId(), "FirmID");
    EXPECT_EQ(item.getFirm().getCountry(), "Country");
}

TEST(ProductTest, UpdateQuantity) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("Grzegorz", "Król", 50, 8000.0, 25);
    Worker worker("Franciszek", "Zielony", 45, Post::PhysicalLabor, 4000.0, 20);
    worker.addOpinion("Doswiadczony");
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Test Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 10);

    product.updateQuantity(3);
    EXPECT_EQ(product.getQuantity(), 7);
}

