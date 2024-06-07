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


TEST(InvoiceTest, GenerateNewDocument) {
    Manager manager("John", "Doe", 45, 5000, 20);
    auto customer = std::make_shared<Customer>("Alice", "Johnson", 35);
    Invoice invoice("INV12345", manager, customer);

    std::vector<ShipmentDetail> products;
    Item item1("Product1", 100.0, ProductType::Electronics, 10.0, std::time(nullptr) + 3600 * 24 * 365);
    products.emplace_back(item1, 2, std::time(nullptr));
    std::string path = "test_invoice.txt";

    invoice.GenerateDocument(products, path);

    std::ifstream file(path);
    ASSERT_TRUE(file.is_open());
    std::string line;
    bool foundInvoiceNumber = false;
    bool foundSeller = false;
    bool foundBuyer = false;
    bool foundProduct = false;
    bool foundTotalNet = false;
    bool foundTotalTax = false;
    bool foundTotalDue = false;

    while (std::getline(file, line)) {
        if (line.find("Invoice Number: INV12345") != std::string::npos) {
            foundInvoiceNumber = true;
        }
        if (line.find("Seller: John Doe") != std::string::npos) {
            foundSeller = true;
        }
        if (line.find("Buyer: Alice Johnson") != std::string::npos) {
            foundBuyer = true;
        }
        if (line.find("Product1") != std::string::npos) {
            foundProduct = true;
        }
        if (line.find("Total Net Amount:") != std::string::npos) {
            foundTotalNet = true;
        }
        if (line.find("Total Tax Amount:") != std::string::npos) {
            foundTotalTax = true;
        }
        if (line.find("Total Amount Due:") != std::string::npos) {
            foundTotalDue = true;
        }
    }

    EXPECT_TRUE(foundInvoiceNumber);
    EXPECT_TRUE(foundSeller);
    EXPECT_TRUE(foundBuyer);
    EXPECT_TRUE(foundProduct);
    EXPECT_TRUE(foundTotalNet);
    EXPECT_TRUE(foundTotalTax);
    EXPECT_TRUE(foundTotalDue);

    std::remove(path.c_str());  
}

TEST(ReceiptTest, GenerateOtherDocument) {
    auto customer = std::make_shared<Customer>("Alice", "Johnson", 35);
    Receipt receipt("Credit Card", customer);

    std::vector<ShipmentDetail> products;
    Item item1("Product1", 100.0, ProductType::Electronics, 10.0, std::time(nullptr) + 3600 * 24 * 365);
    products.emplace_back(item1, 2, std::time(nullptr));
    std::string path = "test_receipt.txt";

    receipt.GenerateDocument(products, path);

    std::ifstream file(path);
    ASSERT_TRUE(file.is_open());
    std::string line;
    bool foundReceipt = false;
    bool foundPaymentMethod = false;
    bool foundProduct = false;
    bool foundTotal = false;

    while (std::getline(file, line)) {
        if (line.find("RECEIPT") != std::string::npos) {
            foundReceipt = true;
        }
        if (line.find("Payment Method: Credit Card") != std::string::npos) {
            foundPaymentMethod = true;
        }
        if (line.find("Product1") != std::string::npos) {
            foundProduct = true;
        }
        if (line.find("Total:") != std::string::npos) {
            foundTotal = true;
        }
    }

    EXPECT_TRUE(foundReceipt);
    EXPECT_TRUE(foundPaymentMethod);
    EXPECT_TRUE(foundProduct);
    EXPECT_TRUE(foundTotal);

    std::remove(path.c_str());  
}

TEST(ReceiptTest, GenerateDocumentWithOverridePaymentMethod) {
    auto customer = std::make_shared<Customer>("Alice", "Johnson", 35);
    Receipt receipt("Credit Card", customer);

    std::vector<ShipmentDetail> products;
    Item item1("Product1", 100.0, ProductType::Electronics, 10.0, std::time(nullptr) + 3600 * 24 * 365);
    products.emplace_back(item1, 2, std::time(nullptr));
    std::string path = "test_receipt_override.txt";

    receipt.GenerateDocument(products, path, "Cash");

    std::ifstream file(path);
    ASSERT_TRUE(file.is_open());
    std::string line;
    bool foundReceipt = false;
    bool foundPaymentMethod = false;
    bool foundProduct = false;
    bool foundTotal = false;

    while (std::getline(file, line)) {
        if (line.find("RECEIPT") != std::string::npos) {
            foundReceipt = true;
        }
        if (line.find("Payment Method: Cash") != std::string::npos) {
            foundPaymentMethod = true;
        }
        if (line.find("Product1") != std::string::npos) {
            foundProduct = true;
        }
        if (line.find("Total:") != std::string::npos) {
            foundTotal = true;
        }
    }

    EXPECT_TRUE(foundReceipt);
    EXPECT_TRUE(foundPaymentMethod);
    EXPECT_TRUE(foundProduct);
    EXPECT_TRUE(foundTotal);

    std::remove(path.c_str());  
}
