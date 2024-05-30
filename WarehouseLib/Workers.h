#pragma once
#include <string>
#include <vector>

class Person {
protected:
	std::string name;
	std::string lastname;
	int age;

public:
	Person(const std::string& name, const std::string& lastname, int age) : name(name), lastname(lastname), age(age) {}
	virtual ~Person() {}
};

class Worker : public Person {
	//TODO
};

class Manager : public Worker {
	//TODO
};

class Customer : public Person {
	//TODO
};

class PrivatePerson : public Customer {
	//TODO
};

class Firm : public Customer {
	//TODO
};