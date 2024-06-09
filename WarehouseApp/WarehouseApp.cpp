#include "../WarehouseLib/Warehouse.h"
#include <iostream>
#include <memory>
#include <string>
#include <ctime>

void createNewWarehouse(Warehouse& warehouse) {
    Manager manager("John", "Doe", 35, 5000, 20);
    Worker worker1("Jane", "Smith", 30, Post::WarehouseManagement, 3000, 5);
    Worker worker2("Alice", "Johnson", 28, Post::PhysicalLabor, 2500, 3);

    warehouse.addManager(std::make_unique<Manager>(manager));
    warehouse.addWorker(std::make_unique<Worker>(worker1));
    warehouse.addWorker(std::make_unique<Worker>(worker2));

    std::vector<ShipmentDetail> items1 = {
        { Item("Laptop", 1000.0, ProductType::Electronics, 0.2, std::time(nullptr) + 3600 * 24 * 365, 2, Firm("TechCorp", "123", "USA")), 10 },
        { Item("Phone", 500.0, ProductType::Electronics, 0.2, std::time(nullptr) + 3600 * 24 * 365, 1, Firm("TechCorp", "123", "USA")), 20 }
    };

    std::vector<ShipmentDetail> items2 = {
        { Item("Shirt", 20.0, ProductType::Apparel, 0.1, std::time(nullptr) + 3600 * 24 * 180, 0, Firm("FashionCo", "456", "UK")), 50 },
        { Item("Pants", 40.0, ProductType::Apparel, 0.1, std::time(nullptr) + 3600 * 24 * 180, 0, Firm("FashionCo", "456", "UK")), 30 }
    };

    warehouse.addShipment(std::make_unique<Shipment>(items1, manager, worker1));
    warehouse.addShipment(std::make_unique<Shipment>(items2, manager, worker2));
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

    while (true) {
        std::cout << "Choose your role:" << std::endl;
        std::cout << "1. Warehouse Manager" << std::endl;
        std::cout << "2. Customer" << std::endl;
        std::cout << "3. Exit" << std::endl;
        int roleOption;
        std::cin >> roleOption;

        if (roleOption == 3) {
            std::cout << "Exiting program." << std::endl;
            break;
        }

        if (roleOption == 1) {
            while (true) {
                std::cout << "Welcome, Warehouse Manager!" << std::endl;
                std::cout << "1. Fire worker" << std::endl;
                std::cout << "2. Add Worker" << std::endl;
                std::cout << "3. Add Shipment" << std::endl;
                std::cout << "4. Generate Document" << std::endl;
                std::cout << "5. Exit to Main Menu" << std::endl;

                int managerOption;
                std::cin >> managerOption;

                if (managerOption == 5) {
                    break;
                }

                switch (managerOption) {
                case 1: {
                    warehouse.listWorkers();
                    std::cout << "Enter the number of the worker to fire: ";
                    size_t workerIndex;
                    std::cin >> workerIndex;
                    if (warehouse.fireWorker(workerIndex)) {
                        std::cout << "Worker fired successfully." << std::endl;
                    }
                    else {
                        std::cout << "Failed to fire worker." << std::endl;
                    }
                    break;
                }
                case 2: {
                    std::string name, lastName;
                    int age, experience;
                    double salary;
                    int post;

                    std::cout << "Enter worker name: ";
                    std::cin >> name;
                    std::cout << "Enter worker last name: ";
                    std::cin >> lastName;
                    std::cout << "Enter worker age: ";
                    std::cin >> age;
                    std::cout << "Enter worker post (0 - Physical Labor, 1 - Warehouse Management): ";
                    std::cin >> post;
                    std::cout << "Enter worker salary: ";
                    std::cin >> salary;
                    std::cout << "Enter worker experience: ";
                    std::cin >> experience;

                    Worker worker(name, lastName, age, static_cast<Post>(post), salary, experience);
                    warehouse.addWorker(std::make_unique<Worker>(worker));
                    std::cout << "Worker added successfully." << std::endl;
                    break;
                }
                case 3: {
                    std::string itemName, firmName, firmId, firmCountry;
                    double itemPrice, itemTax;
                    int itemType, itemWeight, itemQuantity;
                    std::time_t expiryDate;

                    std::cout << "Enter item name: ";
                    std::cin >> itemName;
                    std::cout << "Enter item price: ";
                    std::cin >> itemPrice;
                    std::cout << "Enter item tax: ";
                    std::cin >> itemTax;
                    std::cout << "Enter item type (1 - Perishable, 2 - NonPerishable, 3 - Electronics, 4 - Apparel): ";
                    std::cin >> itemType;
                    std::cout << "Enter item weight: ";
                    std::cin >> itemWeight;
                    std::cout << "Enter item quantity: ";
                    std::cin >> itemQuantity;
                    std::cout << "Enter firm name: ";
                    std::cin >> firmName;
                    std::cout << "Enter firm ID: ";
                    std::cin >> firmId;
                    std::cout << "Enter firm country: ";
                    std::cin >> firmCountry;
                    std::cout << "Enter expiry date (as timestamp): ";
                    std::cin >> expiryDate;

                    std::vector<ShipmentDetail> items = {
                        { Item(itemName, itemPrice, static_cast<ProductType>(itemType - 1), itemTax, expiryDate, itemWeight, Firm(firmName, firmId, firmCountry)), itemQuantity }
                    };

                    Manager& manager = *warehouse.getManagers().front();
                    Worker& worker = *warehouse.getWorkers().front();

                    warehouse.addShipmentAsManager(items, manager, worker);
                    std::cout << "Shipment added successfully." << std::endl;
                    break;
                }
                case 4: {
                    std::string path = "./";
                    warehouse.generateDocument(path);
                    std::cout << "Document generated successfully." << std::endl;
                    break;
                }
                default: {
                    std::cout << "Invalid option for Warehouse Manager." << std::endl;
                    break;
                }
                }
            }
        }
        else if (roleOption == 2) {
            while (true) {
                std::cout << "Welcome, Customer!" << std::endl;
                std::cout << "1. Search Product by Name" << std::endl;
                std::cout << "2. Search Product by Manufacturer" << std::endl;
                std::cout << "3. Search Product by Expiry Date" << std::endl;
                std::cout << "4. Search Product by Type" << std::endl;
                std::cout << "5. Make a Purchase" << std::endl;
                std::cout << "6. Exit to Main Menu" << std::endl;

                int customerOption;
                std::cin >> customerOption;

                if (customerOption == 6) {
                    break;
                }

                switch (customerOption) {
                case 1: {
                    std::string productName;
                    std::cout << "Enter the name of the product: ";
                    std::cin >> productName;
                    auto product = warehouse.searchByName(productName);
                    if (product) {
                        std::cout << "Product found: " << product->getName() << ", Quantity: " << product->getQuantity() << std::endl;
                    }
                    else {
                        std::cout << "Product not found." << std::endl;
                    }
                    break;
                }
                case 2: {
                    std::string manufacturerName;
                    std::cout << "Enter the manufacturer name: ";
                    std::cin >> manufacturerName;
                    auto product = warehouse.searchByManufacturer(manufacturerName);
                    if (product) {
                        std::cout << "Product found: " << product->getName() << ", Quantity: " << product->getQuantity() << std::endl;
                    }
                    else {
                        std::cout << "Product not found." << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::time_t expiryDate;
                    std::cout << "Enter the expiry date (as timestamp): ";
                    std::cin >> expiryDate;
                    auto product = warehouse.searchByExpiryDate(expiryDate);
                    if (product) {
                        std::cout << "Product found: " << product->getName() << ", Quantity: " << product->getQuantity() << std::endl;
                    }
                    else {
                        std::cout << "Product not found." << std::endl;
                    }
                    break;
                }
                case 4: {
                    int productType;
                    std::cout << "Enter the product type (1 - Perishable, 2 - NonPerishable, 3 - Electronics, 4 - Apparel): ";
                    std::cin >> productType;
                    ProductType type = static_cast<ProductType>(productType - 1);
                    auto product = warehouse.searchByType(type);
                    if (product) {
                        std::cout << "Product found: " << product->getName() << ", Quantity: " << product->getQuantity() << std::endl;
                    }
                    else {
                        std::cout << "Product not found." << std::endl;
                    }
                    break;
                }
                case 5: {
                    warehouse.makePurchase();
                    break;
                }
                default: {
                    std::cout << "Invalid option for Customer." << std::endl;
                    break;
                }
                }
            }
        }
        else {
            std::cout << "Invalid role option. Please choose again." << std::endl;
        }
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
