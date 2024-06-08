#include "../WarehouseLib/Items.h"
#include <gtest/gtest.h>
#include <ctime>

TEST(ItemTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Apple", 1.5, ProductType::Perishable, 0.1, expiryDate, 100, firm);
    EXPECT_EQ(item.getName(), "Apple");
    EXPECT_DOUBLE_EQ(item.getPrice(), 1.5);
    EXPECT_EQ(item.getType(), ProductType::Perishable);
    EXPECT_DOUBLE_EQ(item.getTax(), 0.1);
    EXPECT_EQ(item.getExpiryDate(), expiryDate);
    EXPECT_EQ(item.getWeight(), 100);
    EXPECT_EQ(item.getFirm().getFirmName(), "FirmName");
}

TEST(ItemTest, GetName) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Banana", 1.2, ProductType::Perishable, 0.08, expiryDate, 150, firm);
    EXPECT_EQ(item.getName(), "Banana");
}

TEST(ItemTest, GetPrice) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Orange", 2.0, ProductType::Perishable, 0.15, expiryDate, 200, firm);
    EXPECT_DOUBLE_EQ(item.getPrice(), 2.0);
}

TEST(ItemTest, GetType) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Laptop", 1200.0, ProductType::Electronics, 0.2, expiryDate, 3000, firm);
    EXPECT_EQ(item.getType(), ProductType::Electronics);
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

TEST(ShipmentDetailTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Apple", 1.5, ProductType::Perishable, 0.1, expiryDate, 100, firm);
    ShipmentDetail detail(item, 10);
    EXPECT_EQ(detail.item.getName(), "Apple");
    EXPECT_EQ(detail.quantity, 10);
}

TEST(ShipmentDetailTest, Quantity) {
    std::time_t expiryDate = std::time(nullptr);
    Firm firm("FirmName", "FirmID", "Country");
    Item item("Banana", 1.2, ProductType::Perishable, 0.08, expiryDate, 150, firm);
    ShipmentDetail detail(item, 5);
    EXPECT_EQ(detail.quantity, 5);
}

TEST(ProductTest, ConstructorAndGetters) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    std::time_t expiryDate = std::time(nullptr);
    Product product(manager, worker, "Produkt1", 100.0, 0.2, firm, expiryDate, 500, ProductType::Electronics);

    EXPECT_EQ(product.getName(), "Produkt1");
    EXPECT_DOUBLE_EQ(product.getPrice(), 100.0);
    EXPECT_DOUBLE_EQ(product.getTax(), 0.2);
    EXPECT_EQ(product.getFirm().getFirmName(), "FirmName");
    EXPECT_EQ(product.getExpiryDate(), expiryDate);
    EXPECT_EQ(product.getWeight(), 500);
    EXPECT_EQ(product.getType(), ProductType::Electronics);
}

TEST(ProductTest, GetSaleDateAndSetSaleDate) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    std::time_t expiryDate = std::time(nullptr);
    Product product(manager, worker, "Produkt1", 100.0, 0.2, firm, expiryDate, 500, ProductType::Electronics);

    std::time_t saleDate = std::time(nullptr) + 86400;
    product.setSaleDate(saleDate);
    EXPECT_EQ(product.getSaleDate(), saleDate);
}

TEST(ProductTest, IsAvailable) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    std::time_t expiryDate = std::time(nullptr) + 86400;
    Product product(manager, worker, "Produkt1", 100.0, 0.2, firm, expiryDate, 500, ProductType::Electronics);

    EXPECT_TRUE(product.isAvailable());

    product.setSaleDate(std::time(nullptr) - 86400);
    EXPECT_FALSE(product.isAvailable());
}

TEST(ProductTest, SetSaleDateUpdatesValidityTerm) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    std::time_t initialExpiryDate = std::time(nullptr) + 86400;
    Product product(manager, worker, "Produkt1", 100.0, 0.2, firm, initialExpiryDate, 500, ProductType::Electronics);

    std::time_t newSaleDate = std::time(nullptr) + 43200;
    product.setSaleDate(newSaleDate);
    EXPECT_EQ(product.getSaleDate(), newSaleDate);
    EXPECT_EQ(product.getExpiryDate(), newSaleDate);
}