#pragma once
#include <string>
#include <exception>

class DataManager {
public:
    virtual void saveData(const std::string& address) {
        std::terminate();
    }
    virtual void loadData(const std::string& address) {
        std::terminate();
    }
    virtual ~DataManager() = default;
};

class DataWorkers : public DataManager {
public:
    void saveData(const std::string& address) override {
        std::terminate();
    }
    void loadData(const std::string& address) override {
        std::terminate();
    }
};

class DataTransactions : public DataManager {
public:
    void saveData(const std::string& address) override {
        std::terminate();
    }
    void loadData(const std::string& address) override {
        std::terminate();
    }
};

class DataItems : public DataManager {
public:
    void saveData(const std::string& address) override {
        std::terminate();
    }
    void loadData(const std::string& address) override {
        std::terminate();
    }
};