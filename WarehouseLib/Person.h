#pragma once
#include <string>

//DONE

class Person {
protected:
    std::string name;
    std::string lastname;
    int age;

public:
    Person(const std::string& name, const std::string& lastname, int age);
    virtual ~Person();

    std::string getName() const;
    std::string getLastName() const;
    int getAge() const;
};
