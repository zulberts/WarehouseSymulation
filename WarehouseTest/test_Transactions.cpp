#include <gtest/gtest.h>
#include "../WarehouseLib/Transactions.h"
#include "../WarehouseLib/Items.h"
#include "../WarehouseLib/Workers.h"
#include "../WarehouseLib/Customers.h"

TEST(TransactionTest, Constructor) {
    Manager manager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product(manager, worker, "Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics);
    std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>("Customer", "Lastname", 25);

    Transaction transaction(product, 5, 50.0, worker, customer);

    EXPECT_EQ(transaction.getProduct().name, "Product1");
    EXPECT_EQ(transaction.getQuantity(), 5);
    EXPECT_EQ(transaction.getCustomer()->getName(), "Customer");
    EXPECT_FALSE(transaction.isCanceled());
}

TEST(TransactionTest, CalculateTaxAndDiscount) {
    Manager manager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product(manager, worker, "Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics);
    std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>("Customer", "Lastname", 25);

    Transaction transaction(product, 5, 50.0, worker, customer);

    double tax = transaction.calculateTax(0.1);
    double discount = transaction.calculateDiscount(0.2);

    EXPECT_DOUBLE_EQ(tax, 25.0);
    EXPECT_DOUBLE_EQ(discount, 50.0);
}

TEST(TransactionRegisterTest, AddAndFilterTransactions) {
    TransactionRegister registr;
    Manager manager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product1(manager, worker, "Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics);
    Product product2(manager, worker, "Product2", 15.0, 0.15, "Country2", std::time(nullptr) + 1000, 1000, ProductType::Apparel);
    std::shared_ptr<Customer> customer1 = std::make_shared<PrivatePerson>("Customer1", "Lastname1", 25);
    std::shared_ptr<Customer> customer2 = std::make_shared<PrivatePerson>("Customer2", "Lastname2", 30);

    auto transaction1 = std::make_unique<Transaction>(product1, 5, 50.0, worker, customer1);
    auto transaction2 = std::make_unique<Transaction>(product2, 3, 45.0, worker, customer2);

    registr.addTransaction(std::move(transaction1));
    registr.addTransaction(std::move(transaction2));

    auto filteredByCustomer = registr.filterByCustomer(customer1);
    EXPECT_EQ(filteredByCustomer.size(), 1);
    EXPECT_EQ(filteredByCustomer[0]->getCustomer()->getName(), "Customer1");

    std::time_t now = std::time(nullptr);
    auto filteredByDate = registr.filterByDate(now - 1000, now + 1000);
    EXPECT_EQ(filteredByDate.size(), 2);
}

TEST(TransactionRegisterTest, MostFrequentlySoldProducts) {
    TransactionRegister registr;
    Manager manager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product1(manager, worker, "Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics);
    Product product2(manager, worker, "Product2", 15.0, 0.15, "Country2", std::time(nullptr) + 1000, 1000, ProductType::Apparel);
    std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>("Customer", "Lastname", 25);

    auto transaction1 = std::make_unique<Transaction>(product1, 5, 50.0, worker, customer);
    auto transaction2 = std::make_unique<Transaction>(product2, 3, 45.0, worker, customer);
    auto transaction3 = std::make_unique<Transaction>(product1, 2, 20.0, worker, customer);

    registr.addTransaction(std::move(transaction1));
    registr.addTransaction(std::move(transaction2));
    registr.addTransaction(std::move(transaction3));

    auto mostFrequent = registr.mostFrequentlySoldProducts();
    EXPECT_EQ(mostFrequent["Product1"], 7);
    EXPECT_EQ(mostFrequent["Product2"], 3);
}

TEST(TransactionRegisterTest, FilterByCustomerNoMatches) {
    TransactionRegister registr;
    Manager manager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product(manager, worker, "Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics);
    std::shared_ptr<Customer> customer1 = std::make_shared<PrivatePerson>("Customer1", "Lastname1", 25);
    std::shared_ptr<Customer> customer2 = std::make_shared<PrivatePerson>("Customer2", "Lastname2", 30);

    auto transaction = std::make_unique<Transaction>(product, 5, 50.0, worker, customer1);
    registr.addTransaction(std::move(transaction));

    auto filteredByCustomer = registr.filterByCustomer(customer2);
    EXPECT_TRUE(filteredByCustomer.empty());
}

TEST(TransactionRegisterTest, FilterByCustomer) {
    TransactionRegister registr;
    Manager manager("John", "Doe", 45, 5000, 20);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 3000, 5);
    Product product(manager, worker, "TestProduct", 100.0, 0.2, "USA", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Electronics);
    auto customer1 = std::make_shared<Customer>("Alice", "Johnson", 35);
    auto customer2 = std::make_shared<Customer>("Bob", "Smith", 40);

    auto transaction1 = std::make_unique<Transaction>(product, 2, 200.0, worker, customer1);
    auto transaction2 = std::make_unique<Transaction>(product, 3, 300.0, worker, customer2);

    registr.addTransaction(std::move(transaction1));
    registr.addTransaction(std::move(transaction2));

    auto result = registr.filterByCustomer(customer1);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->getCustomer()->getName(), "Alice");
}

TEST(TransactionTest, CancelTransaction) {
    Manager manager("John", "Doe", 45, 5000, 20);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 3000, 5);
    Product product(manager, worker, "TestProduct", 100.0, 0.2, "USA", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Electronics);
    auto customer = std::make_shared<Customer>("Alice", "Johnson", 35);

    Transaction transaction(product, 2, 200.0, worker, customer);
    transaction.cancel();

    EXPECT_TRUE(transaction.isCanceled());
}

TEST(TransactionRegisterTest, AddTransaction) {
    TransactionRegister registr;
    Manager manager("John", "Doe", 45, 5000, 20);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 3000, 5);
    Product product(manager, worker, "TestProduct", 100.0, 0.2, "USA", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Electronics);
    auto customer = std::make_shared<Customer>("Alice", "Johnson", 35);

    auto transaction = std::make_unique<Transaction>(product, 2, 200.0, worker, customer);
    registr.addTransaction(std::move(transaction));

    EXPECT_EQ(registr.getTransactions().size(), 1);
    EXPECT_EQ(registr.getCanceledTransactions().size(), 0);
}

TEST(TransactionRegisterTest, RemoveCanceledTransactions) {
    TransactionRegister registr;
    Manager manager("John", "Doe", 45, 5000, 20);
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 3000, 5);
    Product product(manager, worker, "TestProduct", 100.0, 0.2, "USA", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Electronics);
    auto customer = std::make_shared<Customer>("Alice", "Johnson", 35);

    auto transaction1 = std::make_unique<Transaction>(product, 2, 200.0, worker, customer);
    auto transaction2 = std::make_unique<Transaction>(product, 3, 300.0, worker, customer);
    transaction2->cancel();

    registr.addTransaction(std::move(transaction1));
    registr.addTransaction(std::move(transaction2));
    registr.removeCanceledTransactions();

    EXPECT_EQ(registr.getTransactions().size(), 1);
    EXPECT_EQ(registr.getCanceledTransactions().size(), 1);
}

