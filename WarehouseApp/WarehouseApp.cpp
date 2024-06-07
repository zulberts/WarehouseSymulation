#include "../WarehouseLib/Warehouse.h"
#include "../WarehouseLib/Workers.h"
#include "../WarehouseLib/Customers.h"
#include "../WarehouseLib/Items.h"
#include "../WarehouseLib/Transactions.h"
#include "../WarehouseLib/Shipment.h"
#include <iostream>
#include <memory>
#include <ctime>

// TODO: CORRECT ERRORS
void createNewWarehouse(Warehouse& warehouse) {
    //  todo: addapt to different option of creation warehouse
    std::cout << "Creating a new warehouse..." << std::endl;

    Manager manager("John", "Doe", 35, 5000, 20);
    Firm firm("Ewa", "Czarny", 29, "TechCorp", "12345", "NASDAQ");
    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 3000, 5);
    Product product1(manager, worker, "TestProduct1", 100.0, 0.2, "USA", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Electronics);
    Product product2(manager, worker, "TestProduct2", 100.0, 0.2, "USA", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Apparel);
    auto customer = std::make_shared<Customer>("Alice", "Johnson", 35);

    warehouse.addProduct(std::make_unique<Product>("Product1", 10.0, 0.1, "USA", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Electronics));
    warehouse.addProduct(std::make_unique<Product>("Product2", 20.0, 0.15, "China", std::time(nullptr) + 3600 * 24 * 365, 1, ProductType::Apparel));
    warehouse.addWorker(std::make_unique<Worker>(worker));
    warehouse.addWorker(std::make_unique<Manager>(manager));

    warehouse.addTransaction(std::make_unique<Transaction>(product1, 2, 20.0, worker, &customer));
    warehouse.addTransaction(std::make_unique<Transaction>(product2, 1, 20.0, manager, &firm));

    std::cout << "New warehouse created." << std::endl;
}

int main() {
    Warehouse warehouse;

    char option;
    std::cout << "Do you want to load an existing warehouse? (Y/N): ";
    std::cin >> option;

    if (option == 'Y' || option == 'y') {
        try {
            warehouse.loadFromJson("warehouse.json");
            std::cout << "Warehouse loaded successfully." << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error loading warehouse: " << e.what() << std::endl;
            std::cout << "No warehouses found. Do you want to create a new one? (Y/N): ";
            std::cin >> option;
            if (option == 'Y' || option == 'y') {
                createNewWarehouse(warehouse);
            }
        }
    }
    else {
        createNewWarehouse(warehouse);
    }

    std::cout << "Choose your role:" << std::endl;
    std::cout << "1. Warehouse Manager" << std::endl;
    std::cout << "2. Customer" << std::endl;
    int roleOption;
    std::cin >> roleOption;

    if (roleOption == 1) {

        std::cout << "Welcome, Warehouse Manager!" << std::endl;
        std::cout << "1. Add Product" << std::endl;
        std::cout << "2. Add Worker" << std::endl;
        std::cout << "3. Generate Invoice" << std::endl;
        std::cout << "4. Generate Receipt" << std::endl;
        std::cout << "5. Apply Discounts" << std::endl;

        int managerOption;
        std::cin >> managerOption;

        switch (managerOption) {
        case 1: {
            //todo
            std::string name;
            double price;
            // todo.
            
            std::cout << "Enter product name: ";
            std::cin >> name;
            std::cout << "Enter product price: ";
            std::cin >> price;
            //todo
            // todo
            Product product(/*todo*/);
            warehouse.addProduct(std::make_unique<Product>(product));
            std::cout << "Product added successfully." << std::endl;
            break;
        }
        case 2: {
            // todo
            std::string name;
            //todo
            std::cout << "Enter worker name: ";
            std::cin >> name;
            // todo
            Worker worker(/*todo*/);
            warehouse.addWorker(std::make_unique<Worker>(worker));
            std::cout << "Worker added successfully." << std::endl;
            break;
        }
        case 3: {

            std::string invoiceNumber;

            std::cout << "Enter invoice number: ";
            std::cin >> invoiceNumber;

            std::vector<ShipmentDetail> products; 
            Person seller(/*todo*/);
            std::shared_ptr<Customer> customer = nullptr;  //TODO
            std::string path; // todo

            //TODO
            /*Invoice invoice(invoiceNumber, seller, customer);
            invoice.GenerateDocument(products, path);*/
            std::cout << "Invoice generated successfully." << std::endl;
            break;
        }
        case 4: {

            std::string paymentMethod;

            std::cout << "Enter payment method: ";
            std::cin >> paymentMethod;

            std::vector<ShipmentDetail> products; 
            std::string path; //todo

            std::shared_ptr<Customer> customer = nullptr; // todo: get client
            Receipt receipt(paymentMethod, customer);
            receipt.GenerateDocument(products, path);
            std::cout << "Receipt generated successfully." << std::endl;
            break;
        }
        case 5: {
            //todo
            double discountRate;
            std::time_t daysBeforeExpiry;

            std::cout << "Enter discount rate: ";
            std::cin >> discountRate;
            std::cout << "Enter number of days before expiry: ";
            std::cin >> daysBeforeExpiry;

            warehouse.applyDiscounts(discountRate, daysBeforeExpiry);
            std::cout << "Discounts applied successfully." << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid option for Warehouse Manager. Exiting program." << std::endl;
            return 0;
        }
        }

    }
    else if (roleOption == 2) {

        std::cout << "Welcome, Customer!" << std::endl;
        std::cout << "1. Search Product by Name" << std::endl;
        std::cout << "2. Search Product by Manufacturer" << std::endl;
        std::cout << "3. Search Product by Expiry Date" << std::endl;
        std::cout << "4. Search Product by Type" << std::endl;
        std::cout << "5. View Purchase History" << std::endl;

        int customerOption;
        std::cin >> customerOption;
       
        switch (customerOption) {
        case 1: {
            // TODO
            std::string productName;
            std::cout << "Enter the name of the product: ";
            std::cin >> productName;
            auto products = warehouse.searchByName(productName);
            // TODO : process the 'products' vector containing products with the entered name
            break;
        }
        case 2: {
            // TODO
            std::string manufacturerName;
            std::cout << "Enter the manufacturer name: ";
            std::cin >> manufacturerName;
            auto products = warehouse.searchByManufacturer(manufacturerName);
            // TODO: process the 'products' vector containing products from the entered manufacturer
            break;
        }
        case 3: {
            //TODO
            std::time_t expiryDate;

            std::cout << "Enter the expiry date (YYYY-MM-DD): ";
            std::cin >> expiryDate;
            auto products = warehouse.searchByExpiryDate(expiryDate);
            // TODO: process the 'products' vector containing products expiring on the entered date
            break;
        }
        case 4: {
            // TODO
            int productType;
            std::cout << "Enter the product type (1 - Perishable, 2 - NonePerishable, 3 - Electronics, 4 - Apparel): ";
            std::cin >> productType;
            // Convert user input to ProductType enum
            ProductType type = static_cast<ProductType>(productType - 1);
            auto products = warehouse.searchByType(type);
            // TODO:  process the 'products' vector containing products of the entered type
            break;
        }
        case 5: {

            auto transactions = warehouse.getTransactions();
            // TODO: process the 'transactions' vector containing transaction history
            break;
        }
        default: {
            std::cout << "Invalid option for Customer. Exiting program." << std::endl;
            return 0;
        }
        }
    }
    else {
        std::cout << "Invalid role option. Exiting program." << std::endl;
        return 0;
    }

    std::cout << "Do you want to save the warehouse to a JSON file? (Y/N): ";
    std::cin >> option;

    if (option == 'Y' || option == 'y') {
        try {
            warehouse.saveToJson("warehouse.json");
            std::cout << "Warehouse saved to 'warehouse.json'." << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error saving warehouse to JSON: " << e.what() << std::endl;
        }
    }

    return 0;
}
