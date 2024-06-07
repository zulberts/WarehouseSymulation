#include "../WarehouseLib/Items.h"
#include <gtest/gtest.h>

TEST(ItemTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Apple", 1.5, ProductType::Perishable, 0.1, expiryDate);
    EXPECT_EQ(item.getName(), "Apple");
    EXPECT_DOUBLE_EQ(item.getPrice(), 1.5);
    EXPECT_EQ(item.getType(), ProductType::Perishable);
    EXPECT_DOUBLE_EQ(item.getTax(), 0.1);
    EXPECT_EQ(item.getExpiryDate(), expiryDate);
}

TEST(ItemTest, GetName) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Banana", 1.2, ProductType::Perishable, 0.08, expiryDate);
    EXPECT_EQ(item.getName(), "Banana");
}

TEST(ItemTest, GetPrice) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Orange", 2.0, ProductType::Perishable, 0.15, expiryDate);
    EXPECT_DOUBLE_EQ(item.getPrice(), 2.0);
}

TEST(ItemTest, GetType) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Laptop", 1200.0, ProductType::Electronics, 0.2, expiryDate);
    EXPECT_EQ(item.getType(), ProductType::Electronics);
}

TEST(ItemTest, GetTax) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Shirt", 50.0, ProductType::Apparel, 0.05, expiryDate);
    EXPECT_DOUBLE_EQ(item.getTax(), 0.05);
}

TEST(ItemTest, GetExpiryDate) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Milk", 3.0, ProductType::Perishable, 0.1, expiryDate);
    EXPECT_EQ(item.getExpiryDate(), expiryDate);
}

TEST(ShipmentDetailTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Apple", 1.5, ProductType::Perishable, 0.1, expiryDate);
    std::time_t deliveryDate = std::time(nullptr) + 86400;
    ShipmentDetail detail(item, 10, deliveryDate);
    EXPECT_EQ(detail.item.getName(), "Apple");
    EXPECT_EQ(detail.quantity, 10);
    EXPECT_EQ(detail.deliveryDate, deliveryDate);
}

TEST(ShipmentDetailTest, Quantity) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Banana", 1.2, ProductType::Perishable, 0.08, expiryDate);
    std::time_t deliveryDate = std::time(nullptr) + 86400;
    ShipmentDetail detail(item, 5, deliveryDate);
    EXPECT_EQ(detail.quantity, 5);
}

TEST(ProductTest, ConstructorAndGetters) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t expiryDate = std::time(nullptr);
    Product product(manager, worker, "Produkt1", 100.0, 0.2, "Polska", expiryDate, 500, ProductType::Electronics);

    EXPECT_EQ(product.name, "Produkt1");
    EXPECT_DOUBLE_EQ(product.price, 100.0);
    EXPECT_DOUBLE_EQ(product.tax, 0.2);
    EXPECT_EQ(product.country, "Polska");
    EXPECT_EQ(product.validity_term, expiryDate);
    EXPECT_EQ(product.weight, 500);
    EXPECT_EQ(product.type, ProductType::Electronics);
}

TEST(ProductTest, GetSaleDateAndSetSaleDate) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t expiryDate = std::time(nullptr);
    Product product(manager, worker, "Produkt1", 100.0, 0.2, "Polska", expiryDate, 500, ProductType::Electronics);

    std::time_t saleDate = std::time(nullptr) + 86400;
    product.setSaleDate(saleDate);
    EXPECT_EQ(product.getSaleDate(), saleDate);
}

TEST(ProductTest, IsAvailable) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t expiryDate = std::time(nullptr) + 86400;
    Product product(manager, worker, "Produkt1", 100.0, 0.2, "Polska", expiryDate, 500, ProductType::Electronics);

    EXPECT_TRUE(product.isAvailable());

    product.setSaleDate(std::time(nullptr) - 86400);
    EXPECT_FALSE(product.isAvailable());
}

TEST(ProductTest, SetSaleDateUpdatesValidityTerm) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t initialExpiryDate = std::time(nullptr) + 86400;
    Product product(manager, worker, "Produkt1", 100.0, 0.2, "Polska", initialExpiryDate, 500, ProductType::Electronics);

    std::time_t newSaleDate = std::time(nullptr) + 43200;
    product.setSaleDate(newSaleDate);
    EXPECT_EQ(product.getSaleDate(), newSaleDate);
    EXPECT_EQ(product.validity_term, newSaleDate);
}
