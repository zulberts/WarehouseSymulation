#include <gtest/gtest.h>
#include "..\WarehouseLib\Warehouse.h"
#include "..\WarehouseLib\Items.h"


TEST(WarehouseTest, EmptyWarehouseTest) {
    Warehouse warehouse;

    auto result1 = warehouse.searchByName("Apple");
    auto result2 = warehouse.searchByManufacturer("USA");
    auto result3 = warehouse.searchByExpiryDate(std::time(nullptr));
    auto result4 = warehouse.searchByType(ProductType::Electronics);

    EXPECT_TRUE(result1.empty());
    EXPECT_TRUE(result2.empty());
    EXPECT_TRUE(result3.empty());
    EXPECT_TRUE(result4.empty());
}

TEST(WarehouseTest, SearchByValidityTermTest) {
    Warehouse warehouse;
    std::time_t now = std::time(nullptr);
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Milk", 2.0, 0.1, "France", now - 86400, 500, ProductType::Perishable); 
    auto product2 = std::make_unique<Product>(manager, worker, "Cheese", 5.0, 0.1, "Italy", now + 86400, 500, ProductType::Perishable); 
    auto product3 = std::make_unique<Product>(manager, worker, "Bread", 1.5, 0.1, "Germany", now + 172800, 500, ProductType::Perishable);

    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));
    warehouse.addProduct(std::move(product3));

    auto result = warehouse.searchByExpiryDate(now + 86400);

    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->name, "Cheese");
}

TEST(WarehouseTest, SearchByInvalidTypeTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Laptop", 1000.0, 0.2, "China", std::time(nullptr), 2000, ProductType::Electronics);
    auto product2 = std::make_unique<Product>(manager, worker, "T-Shirt", 20.0, 0.1, "Bangladesh", std::time(nullptr), 300, ProductType::Apparel);

    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));

    auto result = warehouse.searchByType(ProductType::Perishable);

    EXPECT_TRUE(result.empty());
}

TEST(WarehouseTest, AddMultipleProductsTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Apple", 1.0, 0.1, "USA", std::time(nullptr), 100, ProductType::Perishable);
    auto product2 = std::make_unique<Product>(manager, worker, "Banana", 1.2, 0.1, "Ecuador", std::time(nullptr), 120, ProductType::Perishable);
    auto product3 = std::make_unique<Product>(manager, worker, "Laptop", 1000.0, 0.2, "China", std::time(nullptr), 2000, ProductType::Electronics);

    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));
    warehouse.addProduct(std::move(product3));

    auto appleResult = warehouse.searchByName("Apple");
    auto bananaResult = warehouse.searchByName("Banana");
    auto laptopResult = warehouse.searchByName("Laptop");

    ASSERT_EQ(appleResult.size(), 1);
    ASSERT_EQ(bananaResult.size(), 1);
    ASSERT_EQ(laptopResult.size(), 1);
}

TEST(WarehouseTest, SearchByNonexistentNameTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "Apple", 1.0, 0.1, "USA", std::time(nullptr), 100, ProductType::Perishable);
    warehouse.addProduct(std::move(product));

    auto result = warehouse.searchByName("Banana");
    EXPECT_TRUE(result.empty());
}

TEST(WarehouseTest, SearchByNonexistentManufacturerTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "Laptop", 1000.0, 0.2, "China", std::time(nullptr), 2000, ProductType::Electronics);
    warehouse.addProduct(std::move(product));

    auto result = warehouse.searchByManufacturer("USA");
    EXPECT_TRUE(result.empty());
}

TEST(WarehouseTest, SearchByNonexistentExpiryDateTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "Milk", 2.0, 0.1, "France", std::time(nullptr), 500, ProductType::Perishable);
    warehouse.addProduct(std::move(product));

    auto result = warehouse.searchByExpiryDate(std::time(nullptr) + 86400); // 1 day later
    EXPECT_TRUE(result.empty());
}

TEST(WarehouseTest, SearchByNonexistentTypeTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "T-Shirt", 20.0, 0.1, "Bangladesh", std::time(nullptr), 300, ProductType::Apparel);
    warehouse.addProduct(std::move(product));

    auto result = warehouse.searchByType(ProductType::Electronics);
    EXPECT_TRUE(result.empty());
}

TEST(WarehouseTest, AddProductTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "Apple", 1.0, 0.1, "USA", std::time(nullptr), 100, ProductType::Perishable);
    warehouse.addProduct(std::move(product));
    auto result = warehouse.searchByName("Apple");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->name, "Apple");
}

TEST(WarehouseTest, SearchByNameTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product1 = std::make_unique<Product>(manager, worker, "Banana", 1.2, 0.1, "Ecuador", std::time(nullptr), 120, ProductType::Perishable);
    auto product2 = std::make_unique<Product>(manager, worker, "Banana", 1.3, 0.1, "Ecuador", std::time(nullptr), 130, ProductType::Perishable);
    warehouse.addProduct(std::move(product1));
    warehouse.addProduct(std::move(product2));
    auto result = warehouse.searchByName("Banana");
    ASSERT_EQ(result.size(), 2);
}

TEST(WarehouseTest, SearchByManufacturerTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "Laptop", 1000.0, 0.2, "China", std::time(nullptr), 2000, ProductType::Electronics);
    warehouse.addProduct(std::move(product));
    auto result = warehouse.searchByManufacturer("China");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->country, "China");
}

TEST(WarehouseTest, SearchByExpiryDateTest) {
    Warehouse warehouse;
    std::time_t now = std::time(nullptr);
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "Milk", 2.0, 0.1, "France", now, 500, ProductType::Perishable);
    warehouse.addProduct(std::move(product));
    auto result = warehouse.searchByExpiryDate(now);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->validity_term, now);
}

TEST(WarehouseTest, SearchByTypeTest) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 45, 6000, 10);
    Worker worker("Jane", "Smith", 30, Post::PhysicalLabor, 3000, 5);

    auto product = std::make_unique<Product>(manager, worker, "T-Shirt", 20.0, 0.1, "Bangladesh", std::time(nullptr), 300, ProductType::Apparel);
    warehouse.addProduct(std::move(product));
    auto result = warehouse.searchByType(ProductType::Apparel);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->type, ProductType::Apparel);
}

