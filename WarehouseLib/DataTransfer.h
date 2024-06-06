#pragma once
#include <iostream>
#include "Warehouse.h"



class DataTransfer {
public:
    static void saveToJson(const Warehouse& warehouse, const std::string& filename);
    static Warehouse loadFromJson(const std::string& filename);
};


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