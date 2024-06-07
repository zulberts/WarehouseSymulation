#include "../WarehouseLib/Person.h"
#include <gtest/gtest.h>

TEST(PersonTest, ConstructorAndGetters) {
    Person person("John", "Doe", 30);
    EXPECT_EQ(person.getName(), "John");
    EXPECT_EQ(person.getLastName(), "Doe");
    EXPECT_EQ(person.getAge(), 30);
}

TEST(PersonTest, GetName) {
    Person person("Alice", "Smith", 25);
    EXPECT_EQ(person.getName(), "Alice");
}

TEST(PersonTest, GetLastName) {
    Person person("Bob", "Johnson", 40);
    EXPECT_EQ(person.getLastName(), "Johnson");
}

TEST(PersonTest, GetAge) {
    Person person("Charlie", "Brown", 35);
    EXPECT_EQ(person.getAge(), 35);
}

TEST(PersonTest, ConstructorMinimalData) {
    Person person("", "", 0);
    EXPECT_EQ(person.getName(), "");
    EXPECT_EQ(person.getLastName(), "");
    EXPECT_EQ(person.getAge(), 0);
}

TEST(PersonTest, ConstructorMaximalData) {
    Person person("LongNameLongNameLongName", "LongLastNameLongLastNameLongLastName", 120);
    EXPECT_EQ(person.getName(), "LongNameLongNameLongName");
    EXPECT_EQ(person.getLastName(), "LongLastNameLongLastNameLongLastName");
    EXPECT_EQ(person.getAge(), 120);
}
