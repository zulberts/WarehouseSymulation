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

	std::string getName() const;
	std::string getLastName() const;
	int getAge() const;
};

class Worker : public Person {
	//TODO
protected:
	std::string post;
	double salary;
	int seniority;
	std::vector<std::string> opinions;

public:
	Worker(const std::string& name, const std::string& lastname, int age,
		const std::string& post, double salary, int seniority);

	std::string getPost() const;
	double getSalary() const;
	int getSeniority() const;
	std::string operator[](int index) const;
	void addOpinion(const std::string& opinions);
};

class Manager : public Worker {
	//TODO
protected:
	std::vector<Worker*> subordinates;

public:
	Manager(const std::string& name, const std::string& lastname, int age,
		const std::string& post, double salary, int seniority);

	void employWorker(Worker* worker);
	void dismissWorker(Worker* worker);
	void generateReport() const;
};

class Customer : public Person {
	//TODO

protected:
	std::vector<std::string> purchaseHistory;

public:
	Customer(const std::string& name, const std::string& lastname, int age);

	void addPurchase(const std::string& item);
	virtual double calculateDiscount() const;
	// getpurchaseHistory() const;

};

class PrivatePerson : public Customer {
	//TODO

protected:
	std::vector<std::string> purchasePreferences;

public:
	PrivatePerson(const std::string& name, const std::string& lastname, int age);

	void addPreference(const std::string& preference);
	// with operator[]?
	//std::string getPreference() const;
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