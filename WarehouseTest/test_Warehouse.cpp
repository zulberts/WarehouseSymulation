#include <gtest/gtest.h>
#include "../WarehouseLib/Warehouse.h"
#include "../WarehouseLib/Items.h"
#include "../WarehouseLib/Workers.h"
#include "../WarehouseLib/Customers.h"

TEST(WarehouseTest, AddAndSearchProduct) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 40, 6000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 5000.0, 5);

    auto product = std::make_unique<Product>(manager, worker, "Apple", 1.0, 0.1, "USA", std::time(nullptr) + 86400, 100, ProductType::Perishable);
    warehouse.addProduct(std::move(product));

    auto products = warehouse.searchByName("Apple");
    ASSERT_EQ(products.size(), 1);
    EXPECT_EQ(products[0]->name, "Apple");
}

TEST(WarehouseTest, AddAndRetrieveTransaction) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 40, 6000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 5000.0, 5);
    auto product = std::make_unique<Product>(manager, worker, "Apple", 1.0, 0.1, "USA", std::time(nullptr) + 86400, 100, ProductType::Perishable);
    auto customer = std::make_shared<PrivatePerson>("Alice", "Johnson", 25);

    auto transaction = std::make_unique<Transaction>(*product, 5, 5.0, worker, customer);
    warehouse.addTransaction(std::move(transaction));

    const auto& transactions = warehouse.getTransactions();
    ASSERT_EQ(transactions.size(), 1);
    EXPECT_EQ(transactions[0]->getProduct().name, "Apple");
    EXPECT_EQ(transactions[0]->getCustomer()->getName(), "Alice");
}

TEST(WarehouseTest, GenerateInvoice) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 40, 6000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 5000.0, 5);
    auto product = std::make_unique<Product>(manager, worker, "Laptop", 1000.0, 0.2, "China", std::time(nullptr) + 86400 * 30, 2000, ProductType::Electronics);
    auto customer = std::make_shared<Firm>("TechCorp", "Ltd", 10, "Tech Street 1", "Tech City", "Tech Country");

    warehouse.addProduct(std::move(product));
    ASSERT_NO_THROW(warehouse.generateInvoice("INV123", manager, customer, "invoice.txt"));
}

TEST(WarehouseTest, GenerateReceipt) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 40, 6000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 5000.0, 5);
    auto product = std::make_unique<Product>(manager, worker, "Laptop", 1000.0, 0.2, "China", std::time(nullptr) + 86400 * 30, 2000, ProductType::Electronics);
    auto customer = std::make_shared<PrivatePerson>("Alice", "Johnson", 25);

    warehouse.addProduct(std::move(product));
    ASSERT_NO_THROW(warehouse.generateReceipt("Credit Card", customer, "receipt.txt"));
}

TEST(WarehouseTest, ApplyDiscounts) {
    Warehouse warehouse;
    Manager manager("John", "Doe", 40, 6000.0, 10);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 5000.0, 5);
    auto product = std::make_unique<Product>(manager, worker, "Banana", 2.0, 0.1, "Ecuador", std::time(nullptr) + 2 * 86400, 100, ProductType::Perishable);
    warehouse.addProduct(std::move(product));

    warehouse.applyDiscounts(0.5, 3);

    auto products = warehouse.searchByName("Banana");
    ASSERT_EQ(products.size(), 1);
    EXPECT_DOUBLE_EQ(products[0]->price, 1.0);
}
