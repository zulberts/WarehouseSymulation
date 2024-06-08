#include "Workers.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

// DONE

Worker::Worker(const std::string& name, const std::string& lastname, int age,
    Post post, double salary, int experience)
    : Person(name, lastname, age), post(post), salary(salary), experience(experience) {}

Post Worker::getPost() const {
    return post;
}

double Worker::getSalary() const {
    return salary;
}

int Worker::getExperience() const {
    return experience;
}

std::string Worker::operator[](int index) const {
    if (index < 0 || index >= static_cast<int>(opinions.size())) {
        throw std::out_of_range("Index out of range");
    }
    return opinions[index];
}

void Worker::addOpinion(const std::string& opinion) {
    opinions.push_back(opinion);
}

std::string Worker::getOpinions() const {
    std::ostringstream oss;
    oss << "Opinions:\n";
    for (size_t i = 0; i < opinions.size(); ++i) {
        oss << std::to_string(i + 1) + ". " + opinions[i] + "\n";
    }
    return oss.str();
}

Manager::Manager(const std::string& name, const std::string& lastname, int age,
    double salary, int seniority)
    : Worker(name, lastname, age, Post::Other, salary, seniority) {}

Post Manager::getPost() const {
    return post;
}

double Manager::getSalary() const {
    return salary;
}

int Manager::getExperience() const {
    return experience;
}

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
    std::ostringstream report;
    report << "Employee performance report:\n";
    for (const Worker* worker : subordinates) {
        report << worker->getName() << " " << worker->getLastName() << "\n"
            << worker->getOpinions();
    }
    return report.str();
}
