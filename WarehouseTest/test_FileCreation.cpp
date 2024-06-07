#include <gtest/gtest.h>
#include "../WarehouseLib/FileCreation.h"
#include "../WarehouseLib/Items.h"
#include "../WarehouseLib/Workers.h"
#include "../WarehouseLib/Customers.h"
#include <fstream>

TEST(InvoiceTest, GenerateDocument) {
    Manager manager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product(manager, worker, "Laptop", 1000.0, 0.2, "Poland", std::time(nullptr) + 86400, 2, ProductType::Electronics);
    std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>("Customer", "Lastname", 25);
    Person seller("Seller", "Lastname", 40);

    Item item(product.name, product.price, product.type, product.tax, product.validity_term);
    ShipmentDetail detail(item, 1, std::time(nullptr));
    std::vector<ShipmentDetail> products = { detail };

    Invoice invoice("INV-12345", seller, customer);
    invoice.GenerateDocument(products, "invoice.txt");

    std::ifstream file("invoice.txt");
    ASSERT_TRUE(file.is_open());
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    EXPECT_NE(content.find("INVOICE"), std::string::npos);
    EXPECT_NE(content.find("Invoice Number: INV-12345"), std::string::npos);
    EXPECT_NE(content.find("Seller: Seller Lastname"), std::string::npos);
    EXPECT_NE(content.find("Buyer: Customer Lastname"), std::string::npos);
    file.close();
}

TEST(ReceiptTest, GenerateDocument) {
    Manager manager("Manager", "Lastname", 40, 10000.0, 10);
    Worker worker("Worker", "Lastname", 30, Post::WarehouseManagement, 5000.0, 5);
    Product product(manager, worker, "Laptop", 1000.0, 0.2, "Poland", std::time(nullptr) + 86400, 2, ProductType::Electronics);
    std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>("Customer", "Lastname", 25);

    Item item(product.name, product.price, product.type, product.tax, product.validity_term);
    ShipmentDetail detail(item, 1, std::time(nullptr));
    std::vector<ShipmentDetail> products = { detail };

    Receipt receipt("Credit Card", customer);
    receipt.GenerateDocument(products, "receipt.txt");

    std::ifstream file("receipt.txt");
    ASSERT_TRUE(file.is_open());
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    EXPECT_NE(content.find("RECEIPT"), std::string::npos);
    EXPECT_NE(content.find("Payment Method: Credit Card"), std::string::npos);
    file.close();
}