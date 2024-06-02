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

TEST(PersonTest, NegativeAge) {
    Person person("Negative", "Age", -5);
    EXPECT_EQ(person.getAge(), -5);
}

TEST(PersonTest, EmptyValues) {
    Person person("", "", 0);
    EXPECT_EQ(person.getName(), "");
    EXPECT_EQ(person.getLastName(), "");
    EXPECT_EQ(person.getAge(), 0);
}

TEST(PersonTest, ComparisonSameValues) {
    Person person1("John", "Doe", 30);
    Person person2("John", "Doe", 30);
    EXPECT_EQ(person1.getName(), person2.getName());
    EXPECT_EQ(person1.getLastName(), person2.getLastName());
    EXPECT_EQ(person1.getAge(), person2.getAge());
}

TEST(PersonTest, ComparisonDifferentValues) {
    Person person1("Jane", "Doe", 28);
    Person person2("John", "Smith", 30);
    EXPECT_NE(person1.getName(), person2.getName());
    EXPECT_NE(person1.getLastName(), person2.getLastName());
    EXPECT_NE(person1.getAge(), person2.getAge());
}