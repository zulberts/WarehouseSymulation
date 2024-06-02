#include "Workers.h"
#include <stdexcept>
#include <iostream>
#include <sstream>


Person::Person(const std::string& name, const std::string& lastname, int age) : name(name), lastname(lastname), age(age) {}

Person::~Person() {}

std::string Person::getName() const {
    return this->name;
}

std::string Person::getLastName() const {
    return this->lastname;
}

int Person::getAge() const {
    return this->age;
}


Worker::Worker(const std::string& name, const std::string& lastname, int age,
    const Post post, double salary, int seniority)
    : Person(name, lastname, age), post(post), salary(salary), seniority(seniority) {}

std::string Worker::getPost() const {
    return this->post;
}

double Worker::getSalary() const {
    return this->salary;
}

int Worker::getSeniority() const {
    return this->seniority;
}

std::string Worker::operator[](int index) const {
    try {
        if (index < 0 || index >= sizeof(opinions) / sizeof(opinions[index])) {
            throw std::out_of_range("Index out of range");
        }
        return opinions[index];
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Out of range exception caught: " << e.what() << std::endl;
    }
}

void Worker::addOpinion(const std::string& opinion) {
    opinions.push_back(opinion);
}

std::string Worker::getOpinions() const
{
    std::string opinion = "Opinions:\n";
    for (int i{}; i < sizeof(opinions) / sizeof(opinion[0]); ++i)
    {
        opinion += std::to_string(i + 1) + ". " + opinion[i] + "\n";
    }
    return opinion;
}


Manager::Manager(const std::string& name, const std::string& lastname, int age,
    const std::string& post, double salary, int seniority) : Worker(name, lastname, age, post, salary, seniority) {}

void Manager::employWorker(Worker* worker) {
    subordinates.push_back(worker);
}

void Manager::dismissWorker(Worker* worker) {
    auto it = std::find(subordinates.begin(), subordinates.end(), worker);
    if (it != subordinates.end()) {
        subordinates.erase(it);
    }
}


std::string Manager::generateReport() const {
    std::string report = "Employee performance report:\n";
    for (Worker* worker : subordinates) {
        report += worker->getName() + " " + worker->getLastName() + "\n" + worker->getOpinions();
    }
    return report;
}


Customer::Customer(const std::string& name, const std::string& lastname, int age)
    : Person(name, lastname, age) {}

void Customer::addPurchase(const Product& product) {
    purchaseHistory.push_back(product);
}

std::string Customer::getpurchaseHistory() const
{
    std::ostringstream oss;
    oss << "Purchase history:\n";
    for (const auto& product : purchaseHistory) {
        oss << "Product name: " << product.name << "\n"
            << "Price: " << product.price << "\n"
            << "Country: " << product.country << "\n";
    }
    return oss.str();
}

PrivatePerson::PrivatePerson(const std::string& name, const std::string& lastname, int age)
    : Customer(name, lastname, age) {}

void PrivatePerson::addPreference(const Item& preference) {
    purchasePreferences.push_back(preference);
}


Item PrivatePerson::getPreference(ProductType type) const
{
    for (const auto& item : purchasePreferences) {
        if (item.getType() == type) {
            return item;
        }
    }
    throw std::runtime_error("No preference found for the given product type.");
}


double PrivatePerson::calculateDiscount() const {
    int purchaseAmount = purchaseHistory.size();

    if (purchaseAmount > 50) {
        return 0.3;
    }
    else if (purchaseAmount > 35) {
        return 0.2;
    }
    else if (purchaseAmount > 20) {
        return 0.1;
    }
    else if (purchaseAmount > 10) {
        return 0.05;
    }

    return 0.0;
}


Firm::Firm(const std::string& name, const std::string& lastname, int age, 
    const std::string& firmName, const std::string& id, const std::string& exchange)
    : Customer(name, lastname, age), firmName(firmName), id(id), exchange(exchange) {}

std::string Firm::getfirmName() const {
    return this->firmName;
}

std::string Firm::getId() const {
    return this->id;
}

std::string Firm::getExchange() const {
    return this->exchange;
}

double Firm::calculateDiscount() const {
    double summaryValue = 0;
    for (const auto& purchase : purchaseHistory) {
        summaryValue += purchase.price;
    }

    if (summaryValue > 100000) {
        return 0.5; 
    }
    else if (summaryValue > 80000) {
        return 0.4; 
    }
    else if (summaryValue > 60000) {
        return 0.3; 
    }
    else if (summaryValue > 40000) {
        return 0.2; 
    }
    else if (summaryValue > 20000) {
        return 0.1; 
    }
    else if (summaryValue > 10000) {
        return 0.05;
    }

     return 0.0;
}
