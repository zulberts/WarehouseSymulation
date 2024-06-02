#pragma once
#include <string>
#include <vector>
#include "Items.h"

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

enum class Post {
	PhysicalLabor,
	WarehouseManagment,
	Other
};

class Worker : public Person {
protected:
	Post post;
	double salary;
	int seniority;
	std::vector<std::string> opinions;

public:
	Worker(const std::string& name, const std::string& lastname, int age,
		const Post post, double salary, int seniority);

	Post getPost() const;
	double getSalary() const;
	int getSeniority() const;
	std::string operator[](int index) const;
	void addOpinion(const std::string& opinions);
	std::string getOpinions() const;
};

class Manager : public Worker {
protected:
	std::vector<Worker*> subordinates;

public:
	Manager(const std::string& name, const std::string& lastname, int age,
		 double salary, int seniority);

	void employWorker(Worker* worker);
	void dismissWorker(Worker* worker);
	std::string generateReport() const;
};

class Customer : public Person {
	//TODO

protected:
	std::vector<Product> purchaseHistory;

public:
	Customer(const std::string& name, const std::string& lastname, int age);

	void addPurchase(const Product& product);
	virtual double calculateDiscount() const;
	std::string getpurchaseHistory() const;

};

class PrivatePerson : public Customer {
	//TODO

protected:
	std::vector<Item> purchasePreferences;

public:
	PrivatePerson(const std::string& name, const std::string& lastname, int age);

	void addPreference(const Item& preference);
	Item getPreference(ProductType type) const;
	double calculateDiscount() const override;

};

class Firm : public Customer {
	//TODO

private:
	std::string firmName;
	std::string id;
	std::string exchange;

public:
	Firm(const std::string& name, const std::string& lastname, int age, 
		const std::string& firmName, const std::string& id, const std::string& exchange);

	std::string getfirmName() const;
	std::string getId() const;
	std::string getExchange() const;
	double calculateDiscount() const override;

};