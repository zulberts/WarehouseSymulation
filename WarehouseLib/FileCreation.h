#pragma once
#include <string>
#include <vector>

class Document {
public:
    virtual void GenerateDocument(const std::vector<Item>& produkty, const std::string& sciezka);
    //TODO
};

class Invoice : public Document {
public:
    void GenerateDocument(const std::vector<Item>& produkty, const std::string& sciezka) override;
    //TODO
};

class Receipt : public Document {
public:
    void GenerateDocument(const std::vector<Item>& produkty, const std::string& sciezka) override;
    //TODO
};