#include "Person.h"

Person::Person(const std::string& name, const std::string& lastname, int age)
    : name(name), lastname(lastname), age(age) {}

Person::~Person() {}

std::string Person::getName() const {
    return name;
}

std::string Person::getLastName() const {
    return lastname;
}

int Person::getAge() const {
    return age;
}
