#include "../WarehouseLib/Shipment.h"
#include <gtest/gtest.h>

TEST(ShipmentTest, ConstructorAndGetters) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t deliveryDate = std::time(nullptr);
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("Jan", "Kowalski", 30);

    std::vector<ShipmentDetail> items;
    items.emplace_back(Item("Laptop", 1000.0, ProductType::Electronics, 0.2, std::time(nullptr) + 86400), 1, std::time(nullptr) + 86400);
    items.emplace_back(Item("Banana", 1.0, ProductType::Perishable, 0.1, std::time(nullptr) + 86400), 10, std::time(nullptr) + 86400);

    Shipment shipment(items, manager, worker, "DHL", deliveryDate, customer);

    EXPECT_EQ(shipment.getProducts().size(), 2);
    EXPECT_EQ(shipment.getReceivingManager().getName(), "Micha³");
    EXPECT_EQ(shipment.getStorageWorker().getName(), "Piotr");
    EXPECT_EQ(shipment.getDeliveryCompany(), "DHL");
    EXPECT_DOUBLE_EQ(shipment.getTotalCost(), (1000.0 + 0.2) * 1 + (1.0 + 0.1) * 10);
    EXPECT_EQ(shipment.getDeliveryDate(), deliveryDate);
    EXPECT_EQ(shipment.getCustomer()->getName(), "Jan");
}

TEST(ShipmentTest, GetTotalCost) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t deliveryDate = std::time(nullptr);
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("Jan", "Kowalski", 30);

    std::vector<ShipmentDetail> items;
    items.emplace_back(Item("Laptop", 1000.0, ProductType::Electronics, 0.2, std::time(nullptr) + 86400), 1, std::time(nullptr) + 86400);
    items.emplace_back(Item("Banana", 1.0, ProductType::Perishable, 0.1, std::time(nullptr) + 86400), 10, std::time(nullptr) + 86400);

    Shipment shipment(items, manager, worker, "DHL", deliveryDate, customer);
    double expectedTotalCost = (1000.0 + 0.2) * 1 + (1.0 + 0.1) * 10;
    EXPECT_DOUBLE_EQ(shipment.getTotalCost(), expectedTotalCost);
}

TEST(ShipmentTest, AddProducts) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t deliveryDate = std::time(nullptr);
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("Jan", "Kowalski", 30);

    std::vector<ShipmentDetail> items;
    items.emplace_back(Item("Laptop", 1000.0, ProductType::Electronics, 0.2, std::time(nullptr) + 86400), 1, std::time(nullptr) + 86400);

    Shipment shipment(items, manager, worker, "DHL", deliveryDate, customer);

    std::vector<ShipmentDetail> newItems;
    newItems.emplace_back(Item("Banana", 1.0, ProductType::Perishable, 0.1, std::time(nullptr) + 86400), 10, std::time(nullptr) + 86400);
    shipment.addProducts(newItems);

    EXPECT_EQ(shipment.getProducts().size(), 2);
    double expectedTotalCost = (1000.0 + 0.2) * 1 + (1.0 + 0.1) * 10;
    EXPECT_DOUBLE_EQ(shipment.getTotalCost(), expectedTotalCost);
}

TEST(ShipmentTest, GetCustomer) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t deliveryDate = std::time(nullptr);
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("Jan", "Kowalski", 30);

    std::vector<ShipmentDetail> items;
    items.emplace_back(Item("Laptop", 1000.0, ProductType::Electronics, 0.2, std::time(nullptr) + 86400), 1, std::time(nullptr) + 86400);

    Shipment shipment(items, manager, worker, "DHL", deliveryDate, customer);

    EXPECT_EQ(shipment.getCustomer()->getName(), "Jan");
    EXPECT_EQ(shipment.getCustomer()->getLastName(), "Kowalski");
    EXPECT_EQ(shipment.getCustomer()->getAge(), 30);
}

TEST(ShipmentTest, GetDeliveryDate) {
    Manager manager("Micha³", "Nowak", 40, 8000, 10);
    Worker worker("Piotr", "Kowalski", 30, Post::WarehouseManagement, 3000, 5);
    std::time_t deliveryDate = std::time(nullptr);
    std::shared_ptr<Customer> customer = std::make_shared<Customer>("Jan", "Kowalski", 30);

    std::vector<ShipmentDetail> items;
    items.emplace_back(Item("Laptop", 1000.0, ProductType::Electronics, 0.2, std::time(nullptr) + 86400), 1, std::time(nullptr) + 86400);

    Shipment shipment(items, manager, worker, "DHL", deliveryDate, customer);

    EXPECT_EQ(shipment.getDeliveryDate(), deliveryDate);
}
