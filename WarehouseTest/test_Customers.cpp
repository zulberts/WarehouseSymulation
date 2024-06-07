#include "../WarehouseLib/Customers.h"
#include <gtest/gtest.h>

TEST(CustomerTest, ConstructorAndGetters) {
    Customer customer("Jan", "Kowalski", 30);
    EXPECT_EQ(customer.getName(), "Jan");
    EXPECT_EQ(customer.getLastName(), "Kowalski");
    EXPECT_EQ(customer.getAge(), 30);
}

TEST(CustomerTest, AddPurchaseAndGetPurchaseHistory) {
    Customer customer("Ewa", "Grzyb", 28);
    Product product1(Manager("ManagerName", "ManagerLastName", 40, 8000, 10),
        Worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5),
        "Laptop", 3000.0, 0.2, "Poland", std::time(nullptr) + 86400, 2, ProductType::Electronics);
    Product product2(Manager("ManagerName", "ManagerLastName", 40, 8000, 10),
        Worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5),
        "Smartphone", 2000.0, 0.15, "Germany", std::time(nullptr) + 86400, 1, ProductType::Electronics);
    customer.addPurchase(product1);
    customer.addPurchase(product2);
    EXPECT_EQ(customer.getPurchaseHistory(), "Purchase history:\nProduct name: Laptop\nPrice: 3000\nCountry: Poland\nProduct name: Smartphone\nPrice: 2000\nCountry: Germany\n");
}

TEST(CustomerTest, CalculateDiscount) {
    Customer customer("Alicja", "Nowak", 25);
    EXPECT_EQ(customer.calculateDiscount(), 0.0);
}

TEST(PrivatePersonTest, ConstructorAndGetters) {
    PrivatePerson privatePerson("Robert", "Wiœniewski", 40);
    EXPECT_EQ(privatePerson.getName(), "Robert");
    EXPECT_EQ(privatePerson.getLastName(), "Wiœniewski");
    EXPECT_EQ(privatePerson.getAge(), 40);
}

TEST(PrivatePersonTest, AddPreferenceAndGetPreference) {
    PrivatePerson privatePerson("Karol", "Zieliñski", 35);
    Item item1("Electronics", 1500.0, ProductType::Electronics, 0.2, std::time(nullptr) + 86400);
    Item item2("Books", 20.0, ProductType::Apparel, 0.1, std::time(nullptr) + 86400);
    privatePerson.addPreference(item1);
    privatePerson.addPreference(item2);
    EXPECT_EQ(privatePerson.getPreference(ProductType::Electronics).getName(), "Electronics");
    EXPECT_EQ(privatePerson.getPreference(ProductType::Apparel).getName(), "Books");
    EXPECT_THROW(privatePerson.getPreference(ProductType::NonePerishable), std::runtime_error);
}

TEST(PrivatePersonTest, CalculateDiscount) {
    PrivatePerson privatePerson("Dawid", "Bia³y", 32);
    for (int i = 0; i < 55; ++i) {
        privatePerson.addPurchase(Product(Manager("ManagerName", "ManagerLastName", 40, 8000, 10),
            Worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5),
            "Product" + std::to_string(i), 100.0, 0.2, "Country", std::time(nullptr) + 86400, 1, ProductType::NonePerishable));
    }
    EXPECT_EQ(privatePerson.calculateDiscount(), 0.3);
}

TEST(FirmTest, ConstructorAndGetters) {
    Firm firm("Ewa", "Czarny", 29, "TechCorp", "12345", "NASDAQ");
    EXPECT_EQ(firm.getName(), "Ewa");
    EXPECT_EQ(firm.getLastName(), "Czarny");
    EXPECT_EQ(firm.getAge(), 29);
    EXPECT_EQ(firm.getFirmName(), "TechCorp");
    EXPECT_EQ(firm.getId(), "12345");
    EXPECT_EQ(firm.getExchange(), "NASDAQ");
}

TEST(FirmTest, CalculateDiscount) {
    Firm firm("Franciszek", "Zielony", 45, "SoftCorp", "67890", "NYSE");
    for (int i = 0; i < 5; ++i) {
        firm.addPurchase(Product(Manager("ManagerName", "ManagerLastName", 40, 8000, 10),
            Worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5),
            "Product" + std::to_string(i), 5000.0, 0.2, "Country", std::time(nullptr) + 86400, 1, ProductType::NonePerishable));
    }
    EXPECT_EQ(firm.calculateDiscount(), 0.1);

    for (int i = 0; i < 20; ++i) {
        firm.addPurchase(Product(Manager("ManagerName", "ManagerLastName", 40, 8000, 10),
            Worker("WorkerName", "WorkerLastName", 30, Post::WarehouseManagement, 3000, 5),
            "Product" + std::to_string(i), 5000.0, 0.2, "Country", std::time(nullptr) + 86400, 1, ProductType::NonePerishable));
    }
    EXPECT_EQ(firm.calculateDiscount(), 0.5);
}
