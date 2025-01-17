#pragma once
#include <string>
#include <vector>
#include "Person.h"

//DONE

enum class Post {
    PhysicalLabor,
    WarehouseManagement,
    Other
};

class Worker : public Person {
protected:
    Post post;
    double salary;
    int experience;
    std::vector<std::string> opinions;

public:
    Worker(const std::string& name, const std::string& lastname, int age,
        Post post, double salary, int experience);

    Post getPost() const;
    double getSalary() const;
    int getExperience() const;
    std::string operator[](int index) const;
    void addOpinion(const std::string& opinion);
    std::string getOpinions() const;
};

class Manager : public Worker {
protected:
    std::vector<Worker*> subordinates;

public:
    Manager(const std::string& name, const std::string& lastname, int age,
        double salary, int expercience);

    void employWorker(Worker* worker);
    void dismissWorker(Worker* worker);
    std::string generateReport() const;

    Post getPost() const;
    double getSalary() const;
    int getExperience() const;
};
