#include "../WarehouseLib/Customers.h"
#include <gtest/gtest.h>

TEST(CustomerTest, Constructor) {
    Customer customer("Jan", "Kowalski", 30);
    EXPECT_EQ(customer.getName(), "Jan");
    EXPECT_EQ(customer.getLastName(), "Kowalski");
    EXPECT_EQ(customer.getAge(), 30);
}

TEST(CustomerTest, GetName) {
    Customer customer("Jan", "Kowalski", 30);
    EXPECT_EQ(customer.getName(), "Jan");
}

TEST(CustomerTest, GetLastName) {
    Customer customer("Jan", "Kowalski", 30);
    EXPECT_EQ(customer.getLastName(), "Kowalski");
}

TEST(CustomerTest, GetAge) {
    Customer customer("Jan", "Kowalski", 30);
    EXPECT_EQ(customer.getAge(), 30);
}

TEST(PrivatePersonTest, PrivatePersonConstructor) {
    PrivatePerson person("Jane", "Doe", 25);
    EXPECT_EQ(person.getName(), "Jane");
    EXPECT_EQ(person.getLastName(), "Doe");
    EXPECT_EQ(person.getAge(), 25);
}

TEST(PrivatePersonTest, GetName) {
    PrivatePerson person("Jane", "Doe", 25);
    EXPECT_EQ(person.getName(), "Jane");
}

TEST(PrivatePersonTest, GetLastName) {
    PrivatePerson person("Jane", "Doe", 25);
    EXPECT_EQ(person.getLastName(), "Doe");
}

TEST(PrivatePersonTest, GetAge) {
    PrivatePerson person("Jane", "Doe", 25);
    EXPECT_EQ(person.getAge(), 25);
}

TEST(FirmTest, FirmConstructor) {
    Firm firm("TechCorp", "12345", "USA");
    EXPECT_EQ(firm.getFirmName(), "TechCorp");
    EXPECT_EQ(firm.getId(), "12345");
    EXPECT_EQ(firm.getCountry(), "USA");
}

TEST(FirmTest, GetFirmName) {
    Firm firm("TechCorp", "12345", "USA");
    EXPECT_EQ(firm.getFirmName(), "TechCorp");
}

TEST(FirmTest, GetId) {
    Firm firm("TechCorp", "12345", "USA");
    EXPECT_EQ(firm.getId(), "12345");
}

TEST(FirmTest, GetCountry) {
    Firm firm("TechCorp", "12345", "USA");
    EXPECT_EQ(firm.getCountry(), "USA");
}
