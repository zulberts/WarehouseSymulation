#include "../WarehouseLib/Transactions.h"
#include <gtest/gtest.h>
#include <ctime>

TEST(TransactionTest, ConstructorAndGetters) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product1(manager, worker, "Product1", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);
    Product product2(manager, worker, "Product2", 15.0, 0.1, firm, expiryDate, 500, ProductType::Apparel, 30);

    std::vector<Product> products = { product1, product2 };
    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);

    Transaction transaction(products, worker, customer);

    EXPECT_EQ(transaction.getProducts().size(), 2);
    EXPECT_EQ(transaction.getProducts()[0].getName(), "Product1");
    EXPECT_EQ(transaction.getProducts()[1].getName(), "Product2");

    EXPECT_EQ(transaction.getWorker().getName(), "WorkerName");
    EXPECT_EQ(transaction.getWorker().getLastName(), "WorkerLastName");

    EXPECT_EQ(transaction.getCustomer()->getName(), "Jane");
    EXPECT_EQ(transaction.getCustomer()->getLastName(), "Doe");

    EXPECT_FALSE(transaction.isCanceled());
}

TEST(TransactionTest, Cancel) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    std::vector<Product> products = { product };
    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);

    Transaction transaction(products, worker, customer);
    transaction.cancel();

    EXPECT_TRUE(transaction.isCanceled());
}

TEST(TransactionTest, GetTransactionTime) {
    std::time_t beforeCreation = std::time(nullptr);

    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    std::vector<Product> products = { product };
    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);

    Transaction transaction(products, worker, customer);

    std::time_t afterCreation = std::time(nullptr);

    EXPECT_LE(transaction.getTransactionTime(), afterCreation);
    EXPECT_GE(transaction.getTransactionTime(), beforeCreation);
}

TEST(TransactionTest, CalculateTotalPriceAndTax) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product1(manager, worker, "Product1", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);
    Product product2(manager, worker, "Product2", 15.0, 0.1, firm, expiryDate, 500, ProductType::Apparel, 30);

    std::vector<Product> products = { product1, product2 };
    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);

    Transaction transaction(products, worker, customer);

    double expectedTotalPrice = 20.0 + 15.0;
    double expectedTotalTax = (20.0 * 0.2) + (15.0 * 0.1);

    EXPECT_DOUBLE_EQ(transaction.getTotalPrice(), expectedTotalPrice);
    EXPECT_DOUBLE_EQ(transaction.getTotalTax(), expectedTotalTax);
}

TEST(TransactionTest, GetProducts) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    std::vector<Product> products = { product };
    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);

    Transaction transaction(products, worker, customer);

    auto transactionProducts = transaction.getProducts();
    EXPECT_EQ(transactionProducts.size(), 1);
    EXPECT_EQ(transactionProducts[0].getName(), "Product");
}

TEST(TransactionTest, GetCustomer) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    std::vector<Product> products = { product };
    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);

    Transaction transaction(products, worker, customer);

    auto transactionCustomer = transaction.getCustomer();
    EXPECT_EQ(transactionCustomer->getName(), "Jane");
    EXPECT_EQ(transactionCustomer->getLastName(), "Doe");
}

TEST(TransactionTest, GetWorker) {
    std::time_t expiryDate = std::time(nullptr);
    Manager manager("ManagerName", "ManagerLastName", 40, 8000, 10);
    Worker worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5);
    Firm firm("FirmName", "FirmID", "Country");
    Product product(manager, worker, "Product", 20.0, 0.2, firm, expiryDate, 1000, ProductType::Electronics, 50);

    std::vector<Product> products = { product };
    auto customer = std::make_shared<PrivatePerson>("Jane", "Doe", 25);

    Transaction transaction(products, worker, customer);

    auto transactionWorker = transaction.getWorker();
    EXPECT_EQ(transactionWorker.getName(), "WorkerName");
    EXPECT_EQ(transactionWorker.getLastName(), "WorkerLastName");
}
