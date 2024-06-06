#include <gtest/gtest.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../WarehouseLib/DataTransfer.h"
#include "../WarehouseLib/Items.h"

TEST(DataTransferTest, SaveToJson) {

    Manager manager("John", "Doe", 45, 1000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 500.0, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Product1", 10.0, 1.0, "USA", 1627841025, 500, ProductType::Electronics);
    auto product2 = std::make_unique<Product>(manager, worker, "Product2", 20.0, 2.0, "Canada", 1627842025, 1000, ProductType::Apparel);

    Warehouse warehouse;
    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));

    std::string testFilename = "test_warehouse.json";

    DataTransfer::saveToJson(warehouse, testFilename);

    std::ifstream file(testFilename);
    ASSERT_TRUE(file.is_open());

    nlohmann::json j;
    file >> j;
    file.close();

    ASSERT_EQ(j["products"].size(), 2);
    EXPECT_EQ(j["products"][0]["name"], "Product1");
    EXPECT_EQ(j["products"][0]["price"], 10.0);
    EXPECT_EQ(j["products"][0]["country"], "USA");

    EXPECT_EQ(j["products"][1]["name"], "Product2");
    EXPECT_EQ(j["products"][1]["price"], 20.0);
    EXPECT_EQ(j["products"][1]["country"], "Canada");

    std::remove(testFilename.c_str());
}

TEST(DataTransferTest, LoadFromJson) {

    Manager manager("John", "Doe", 45, 1000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 500.0, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Product1", 10.0, 1.0, "USA", 1627841025, 500, ProductType::Electronics);
    auto product2 = std::make_unique<Product>(manager, worker, "Product2", 20.0, 2.0, "Canada", 1627842025, 1000, ProductType::Apparel);

    Warehouse warehouse;
    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));

    std::string testFilename = "test_warehouse.json";

    DataTransfer::saveToJson(warehouse, testFilename);

    Warehouse loadedWarehouse = DataTransfer::loadFromJson(testFilename);

    const auto& products = loadedWarehouse.getProducts();
    ASSERT_EQ(products.size(), 2);

    const Product& loadedProduct1 = *products[0];
    EXPECT_EQ(loadedProduct1.name, "Product1");
    EXPECT_EQ(loadedProduct1.price, 10.0);
    EXPECT_EQ(loadedProduct1.country, "USA");

    const Product& loadedProduct2 = *products[1];
    EXPECT_EQ(loadedProduct2.name, "Product2");
    EXPECT_EQ(loadedProduct2.price, 20.0);
    EXPECT_EQ(loadedProduct2.country, "Canada");

    std::remove(testFilename.c_str());
}


TEST(DataTransferTest, SaveAndLoadEmptyWarehouse) {
    Warehouse emptyWarehouse;
    std::string testFilename = "test_empty_warehouse.json";

    DataTransfer::saveToJson(emptyWarehouse, testFilename);

    std::ifstream file(testFilename);
    ASSERT_TRUE(file.is_open());

    nlohmann::json j;
    file >> j;
    file.close();

    ASSERT_EQ(j["products"].size(), 0);

    Warehouse loadedWarehouse = DataTransfer::loadFromJson(testFilename);
    ASSERT_EQ(loadedWarehouse.getProducts().size(), 0);

    std::remove(testFilename.c_str());
}

TEST(DataTransferTest, SaveAndLoadProductDetails) {

    Manager manager("John", "Doe", 45, 1000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 500.0, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Product1", 10.0, 1.0, "USA", 1627841025, 500, ProductType::Electronics);
    product1->setSaleDate(1627845000);
    auto product2 = std::make_unique<Product>(manager, worker, "Product2", 20.0, 2.0, "Canada", 1627842025, 1000, ProductType::Apparel);
    product2->setSaleDate(1627846000);

    Warehouse warehouse;
    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));

    std::string testFilename = "test_product_details.json";

    DataTransfer::saveToJson(warehouse, testFilename);

    Warehouse loadedWarehouse = DataTransfer::loadFromJson(testFilename);

    const auto& products = loadedWarehouse.getProducts();
    ASSERT_EQ(products.size(), 2);

    const Product& loadedProduct1 = *products[0];
    EXPECT_EQ(loadedProduct1.name, "Product1");
    EXPECT_EQ(loadedProduct1.price, 10.0);
    EXPECT_EQ(loadedProduct1.tax, 1.0);
    EXPECT_EQ(loadedProduct1.country, "USA");
    EXPECT_EQ(loadedProduct1.validity_term, 1627845000);
    EXPECT_EQ(loadedProduct1.weight, 500);
    EXPECT_EQ(loadedProduct1.getSaleDate(), 1627845000);
    EXPECT_EQ(loadedProduct1.type, ProductType::Electronics);

    const Product& loadedProduct2 = *products[1];
    EXPECT_EQ(loadedProduct2.name, "Product2");
    EXPECT_EQ(loadedProduct2.price, 20.0);
    EXPECT_EQ(loadedProduct2.tax, 2.0);
    EXPECT_EQ(loadedProduct2.country, "Canada");
    EXPECT_EQ(loadedProduct2.validity_term, 1627846000);
    EXPECT_EQ(loadedProduct2.weight, 1000);
    EXPECT_EQ(loadedProduct2.getSaleDate(), 1627846000);
    EXPECT_EQ(loadedProduct2.type, ProductType::Apparel);

    std::remove(testFilename.c_str());
}

TEST(DataTransferTest, SaveAndLoadProductAvailability) {

    Manager manager("John", "Doe", 45, 1000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 500.0, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Product1", 10.0, 1.0, "USA", 1627841025, 500, ProductType::Electronics);
    product1->setSaleDate(1627845000);
    auto product2 = std::make_unique<Product>(manager, worker, "Product2", 20.0, 2.0, "Canada", 1627842025, 1000, ProductType::Apparel);
    product2->setSaleDate(0);  

    Warehouse warehouse;
    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));

    std::string testFilename = "test_product_availability.json";

    DataTransfer::saveToJson(warehouse, testFilename);

    Warehouse loadedWarehouse = DataTransfer::loadFromJson(testFilename);

    const auto& products = loadedWarehouse.getProducts();
    ASSERT_EQ(products.size(), 2);

    const Product& loadedProduct1 = *products[0];
    EXPECT_FALSE(loadedProduct1.isAvailable());

    const Product& loadedProduct2 = *products[1];
    EXPECT_FALSE(loadedProduct2.isAvailable());

    std::remove(testFilename.c_str());
}

