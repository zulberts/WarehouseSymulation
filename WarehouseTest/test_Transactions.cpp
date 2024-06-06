#include <gtest/gtest.h>
#include "../WarehouseLib/Transactions.h"
#include "../WarehouseLib/Items.h"
#include "../WarehouseLib/Workers.h"

Product createProduct(const std::string& name, double price, double tax, const std::string& country, std::time_t validity, int weight, ProductType type, const Manager& recManager, const Worker& storWorker) {
    return Product(recManager, storWorker, name, price, tax, country, validity, weight, type);
}

Customer createCustomer(const std::string& name, const std::string& lastname, int age) {
    return Customer(name, lastname, age);
}

Worker createWorker(const std::string& name, const std::string& lastname, int age, Post post, double salary, int seniority) {
    return Worker(name, lastname, age, post, salary, seniority);
}

Manager createManager(const std::string& name, const std::string& lastname, int age, double salary, int seniority) {
    return Manager(name, lastname, age, salary, seniority);
}

TEST(TransactionTest, Constructor) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    EXPECT_EQ(transaction.getType(), Transaction::sale);
    EXPECT_EQ(transaction.getProduct().name, "Product1");
    EXPECT_EQ(transaction.getQuantity(), 5);
    EXPECT_EQ(transaction.getCustomer().getName(), "Customer");
    EXPECT_FALSE(transaction.isCanceled());
}

TEST(TransactionTest, GetQuantity) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    EXPECT_EQ(transaction.getQuantity(), 5);
}

TEST(TransactionTest, GetTransactionTime) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    std::time_t transactionTime = transaction.getTransactionTime();
    EXPECT_LE(transactionTime, std::time(nullptr));
}

TEST(TransactionTest, GetType) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    EXPECT_EQ(transaction.getType(), Transaction::sale);
}


TEST(TransactionTest, GetProduct) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    const Product& retrievedProduct = transaction.getProduct();
    EXPECT_EQ(retrievedProduct.name, "Product1");
    EXPECT_DOUBLE_EQ(retrievedProduct.price, 10.0);
}

TEST(TransactionTest, GetCustomer) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    const Customer& retrievedCustomer = transaction.getCustomer();
    EXPECT_EQ(retrievedCustomer.getName(), "Customer");
    EXPECT_EQ(retrievedCustomer.getLastName(), "Lastname");
}

TEST(TransactionTest, CalculateTax) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    double tax = transaction.calculateTax(0.1); 
    EXPECT_DOUBLE_EQ(tax, 25.0);
}

TEST(TransactionTest, CalculateDiscount) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    double discount = transaction.calculateDiscount(0.2);
    EXPECT_DOUBLE_EQ(discount, 50.0);
}

TEST(TransactionTest, CancelTransaction) {
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);

    transaction.cancel();
    EXPECT_TRUE(transaction.isCanceled());
}

TEST(TransactionRegisterTest, AddAndFilterTransactions) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product1 = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Product product2 = createProduct("Product2", 15.0, 0.15, "Country2", std::time(nullptr) + 1000, 1000, ProductType::Apparel, manager, worker);
    Customer customer1 = createCustomer("Customer1", "Lastname1", 25);
    Customer customer2 = createCustomer("Customer2", "Lastname2", 30);

    Transaction transaction1(Transaction::sale, product1, 5, 50.0, worker, customer1);
    Transaction transaction2(Transaction::sale, product2, 3, 45.0, worker, customer2);

    registr.addTransaction(transaction1);
    registr.addTransaction(transaction2);

    auto filteredByCustomer = registr.filterByCustomer(customer1);
    EXPECT_EQ(filteredByCustomer.size(), 1);
    EXPECT_EQ(filteredByCustomer[0].getCustomer().getName(), "Customer1");

    std::time_t now = std::time(nullptr);
    auto filteredByDate = registr.filterByDate(now - 1000, now + 1000);
    EXPECT_EQ(filteredByDate.size(), 2);
}

TEST(TransactionRegisterTest, MostFrequentlySoldProducts) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product1 = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Product product2 = createProduct("Product2", 15.0, 0.15, "Country2", std::time(nullptr) + 1000, 1000, ProductType::Apparel, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction1(Transaction::sale, product1, 5, 50.0, worker, customer);
    Transaction transaction2(Transaction::sale, product2, 3, 45.0, worker, customer);
    Transaction transaction3(Transaction::sale, product1, 2, 20.0, worker, customer);

    registr.addTransaction(transaction1);
    registr.addTransaction(transaction2);
    registr.addTransaction(transaction3);

    auto mostFrequent = registr.mostFrequentlySoldProducts();
    EXPECT_EQ(mostFrequent["Product1"], 7);
    EXPECT_EQ(mostFrequent["Product2"], 3);
}

TEST(TransactionRegisterTest, FilterByDateNoMatches) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    std::time_t now = std::time(nullptr);
    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);
    registr.addTransaction(transaction);

    auto filteredByDate = registr.filterByDate(now - 2000, now - 1000);
    EXPECT_TRUE(filteredByDate.empty());
}

TEST(TransactionRegisterTest, FilterByCustomerNoMatches) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer1 = createCustomer("Customer1", "Lastname1", 25);
    Customer customer2 = createCustomer("Customer2", "Lastname2", 30);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer1);
    registr.addTransaction(transaction);

    auto filteredByCustomer = registr.filterByCustomer(customer2);
    EXPECT_TRUE(filteredByCustomer.empty());
}

TEST(TransactionRegisterTest, AddCanceledTransaction) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);
    transaction.cancel();
    registr.addTransaction(transaction);

    auto mostFrequent = registr.mostFrequentlySoldProducts();
    EXPECT_TRUE(mostFrequent.empty());
}

TEST(TransactionRegisterTest, AddAndCancelTransaction) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);
    registr.addTransaction(transaction);
    transaction.cancel();

    auto mostFrequent = registr.mostFrequentlySoldProducts();
    EXPECT_FALSE(mostFrequent.empty());
}

TEST(TransactionRegisterTest, FilterByDateMultipleTransactions) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    std::time_t now = std::time(nullptr);
    Transaction transaction1(Transaction::sale, product, 5, 50.0, worker, customer);
    Transaction transaction2(Transaction::sale, product, 3, 30.0, worker, customer);

    registr.addTransaction(transaction1);
    registr.addTransaction(transaction2);

    auto filteredByDate = registr.filterByDate(now - 1000, now + 1000);
    EXPECT_EQ(filteredByDate.size(), 2);
}

TEST(TransactionRegisterTest, FilterByDateOutsideRange) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    std::time_t now = std::time(nullptr);
    std::time_t past = now - 5000;
    std::time_t future = now + 5000;

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);
    registr.addTransaction(transaction);

    auto filteredByDate = registr.filterByDate(now + 1000, future);
    EXPECT_TRUE(filteredByDate.empty());

    filteredByDate = registr.filterByDate(past, now - 1000);
    EXPECT_TRUE(filteredByDate.empty());
}

TEST(TransactionRegisterTest, FilterByDifferentCustomers) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer1 = createCustomer("Customer1", "Lastname1", 25);
    Customer customer2 = createCustomer("Customer2", "Lastname2", 30);

    Transaction transaction1(Transaction::sale, product, 5, 50.0, worker, customer1);
    Transaction transaction2(Transaction::sale, product, 3, 30.0, worker, customer2);

    registr.addTransaction(transaction1);
    registr.addTransaction(transaction2);

    auto filteredByCustomer1 = registr.filterByCustomer(customer1);
    EXPECT_EQ(filteredByCustomer1.size(), 1);
    EXPECT_EQ(filteredByCustomer1[0].getCustomer().getName(), "Customer1");

    auto filteredByCustomer2 = registr.filterByCustomer(customer2);
    EXPECT_EQ(filteredByCustomer2.size(), 1);
    EXPECT_EQ(filteredByCustomer2[0].getCustomer().getName(), "Customer2");
}


TEST(TransactionRegisterTest, FilterByDateExactMatch) {
    TransactionRegister registr;
    Manager manager = createManager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker = createWorker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product = createProduct("Product1", 10.0, 0.1, "Country1", std::time(nullptr) + 1000, 500, ProductType::Electronics, manager, worker);
    Customer customer = createCustomer("Customer", "Lastname", 25);

    std::time_t now = std::time(nullptr);

    Transaction transaction(Transaction::sale, product, 5, 50.0, worker, customer);
    registr.addTransaction(transaction);

    auto filteredByDate = registr.filterByDate(now, now);
    EXPECT_EQ(filteredByDate.size(), 1);
    EXPECT_EQ(filteredByDate[0].getTransactionTime(), now);
}