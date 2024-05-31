#include "Workers.h"
#include <stdexcept>
//TODO


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
    const std::string& post, double salary, int seniority)
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

// try-catch
std::string Worker::operator[](int index) const {
    if (index < 0 || index >= sizeof(opinions) / sizeof(opinions[index])) {
        throw std::out_of_range("Index out of range");
    }
    return opinions[index];
}

void Worker::addOpinion(const std::string& opinion) {
    opinions.push_back(opinion);
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

// 
void Manager::generateReport() const {


}


// to change: item as an object of class Item
Customer::Customer(const std::string& name, const std::string& lastname, int age)
    : Person(name, lastname, age) {}

void Customer::addPurchase(const std::string& item) {
    purchaseHistory.push_back(item);
}

PrivatePerson::PrivatePerson(const std::string& name, const std::string& lastname, int age)
    : Customer(name, lastname, age) {}

void PrivatePerson::addPreference(const std::string& preference) {
    purchasePreferences.push_back(preference);
}


double PrivatePerson::calculateDiscount() const {
    // based on what?
    if (purchaseHistory.size() > 5) {
        return 0.05; // discount 5% 
    }
    // add other discounts
    return 0.0;
}


Firm::Firm(const std::string& name, const std::string& lastname, int age, 
    const std::string& nazwaFirmy, const std::string& numerIdentyfikacyjny, const std::string& branza)
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
    if (purchaseHistory.size() > 100) {
        return 0.1; 
    }
    // add other?
    return 0.0;
}
