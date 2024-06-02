#include "../WarehouseLib/Items.h"
#include <gtest/gtest.h>

TEST(ItemTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Apple", 1.5, ProductType::Perishable, 0.1, expiryDate);
    EXPECT_EQ(item.getName(), "Apple");
    EXPECT_EQ(item.getPrice(), 1.5);
    EXPECT_EQ(item.getType(), ProductType::Perishable);
    EXPECT_EQ(item.getTax(), 0.1);
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
    EXPECT_EQ(item.getPrice(), 2.0);
}

TEST(ItemTest, GetType) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Laptop", 1200.0, ProductType::Electronics, 0.2, expiryDate);
    EXPECT_EQ(item.getType(), ProductType::Electronics);
}

TEST(ItemTest, GetTax) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Shirt", 50.0, ProductType::Apparel, 0.05, expiryDate);
    EXPECT_EQ(item.getTax(), 0.05);
}

TEST(ItemTest, GetExpiryDate) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Milk", 3.0, ProductType::Perishable, 0.1, expiryDate);
    EXPECT_EQ(item.getExpiryDate(), expiryDate);
}

TEST(ShipmentDetailTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Apple", 1.5, ProductType::Perishable, 0.1, expiryDate);
    ShipmentDetail detail(item, 10);
    EXPECT_EQ(detail.item.getName(), "Apple");
    EXPECT_EQ(detail.quantity, 10);
}

TEST(ShipmentDetailTest, Quantity) {
    std::time_t expiryDate = std::time(nullptr);
    Item item("Banana", 1.2, ProductType::Perishable, 0.08, expiryDate);
    ShipmentDetail detail(item, 5);
    EXPECT_EQ(detail.quantity, 5);
}

TEST(ShipmentTest, ConstructorAndGetters) {
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    std::vector<ShipmentDetail> items;
    std::time_t expiryDate = std::time(nullptr);
    items.emplace_back(Item("Item1", 10.0, ProductType::Electronics, 0.2, expiryDate), 2);
    items.emplace_back(Item("Item2", 20.0, ProductType::Apparel, 0.15, expiryDate), 3);

    Shipment shipment(items, manager, worker, "DeliveryCompany");
    EXPECT_EQ(shipment.getProducts().size(), 2);
    EXPECT_EQ(shipment.getReceivingManager().getName(), "ManagerName");
    EXPECT_EQ(shipment.getStorageWorker().getName(), "WorkerName");
    EXPECT_EQ(shipment.getDeliveryCompany(), "DeliveryCompany");
}

TEST(ShipmentTest, GetTotalCost) {
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    std::vector<ShipmentDetail> items;
    std::time_t expiryDate = std::time(nullptr);
    items.emplace_back(Item("Item1", 10.0, ProductType::Electronics, 0.2, expiryDate), 2);
    items.emplace_back(Item("Item2", 20.0, ProductType::Apparel, 0.15, expiryDate), 3);

    Shipment shipment(items, manager, worker, "DeliveryCompany");
    double expectedTotalCost = (10.0 * 2) + (20.0 * 3);
    EXPECT_EQ(shipment.getTotalCost(), expectedTotalCost);
}

TEST(ShipmentTest, AddProducts) {
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    std::vector<ShipmentDetail> items;
    std::time_t expiryDate = std::time(nullptr);
    items.emplace_back(Item("Item1", 10.0, ProductType::Electronics, 0.2, expiryDate), 2);

    Shipment shipment(items, manager, worker, "DeliveryCompany");

    std::vector<ShipmentDetail> newItems;
    newItems.emplace_back(Item("Item3", 30.0, ProductType::Apparel, 0.1, expiryDate), 4);
    shipment.addProducts(newItems);

    EXPECT_EQ(shipment.getProducts().size(), 2);
}

TEST(ProductTest, ConstructorAndGetters) {
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t expiryDate = std::time(nullptr);
    Product product(manager, worker, "Product1", 100.0, 0.2, "Country1", expiryDate, 500, ProductType::Electronics);

    EXPECT_EQ(product.name, "Product1");
    EXPECT_EQ(product.price, 100.0);
    EXPECT_EQ(product.tax, 0.2);
    EXPECT_EQ(product.country, "Country1");
    EXPECT_EQ(product.validity_term, expiryDate);
    EXPECT_EQ(product.weight, 500);
    EXPECT_EQ(product.type, ProductType::Electronics);
}

TEST(ProductTest, GetSaleDateAndSetSaleDate) {
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t expiryDate = std::time(nullptr);
    Product product(manager, worker, "Product1", 100.0, 0.2, "Country1", expiryDate, 500, ProductType::Electronics);

    std::time_t saleDate = std::time(nullptr) + 86400; // one day later
    product.setSaleDate(saleDate);
    EXPECT_EQ(product.getSaleDate(), saleDate);
}

TEST(ProductTest, IsAvailable) {
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t expiryDate = std::time(nullptr);
    Product product(manager, worker, "Product1", 100.0, 0.2, "Country1", expiryDate, 500, ProductType::Electronics);

    EXPECT_TRUE(product.isAvailable());

    product.setSaleDate(std::time(nullptr));
    EXPECT_FALSE(product.isAvailable());
}
