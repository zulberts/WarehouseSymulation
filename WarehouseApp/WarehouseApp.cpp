//#include "../WarehouseLib/Warehouse.h"
//#include <iostream>
//#include <memory>
//
//

int main() {
	return 0;
}

//std::unique_ptr<Shipment> createShipment(const Manager& manager, const Worker& worker, const std::string& company, double price, int quantity) {
//    std::vector<ShipmentDetail> items;
//    std::time_t expiryDate = std::time(nullptr) + 3600 * 24 * 365;
//
//    Item item("Laptop", price, ProductType::Electronics, 0.2, expiryDate);
//    items.emplace_back(item, quantity, expiryDate);
//
//    auto customer = std::make_shared<Firm>("Company Representative", "Smith", 40, company, "12345", "NYSE");
//
//    return std::make_unique<Shipment>(items, manager, worker, company, std::time(nullptr), customer);
//}
//
//void createNewWarehouse(Warehouse& warehouse) {
//    std::cout << "Creating a new warehouse..." << std::endl;
//
//    Manager manager("John", "Doe", 35, 5000, 20);
//    Worker worker("Jane", "Smith", 30, Post::WarehouseManagement, 3000, 5);
//
//    auto shipment1 = createShipment(manager, worker, "TechCorp", 1000.0, 100);
//    auto shipment2 = createShipment(manager, worker, "InnoElectronics", 950.0, 200);
//    auto shipment3 = createShipment(manager, worker, "GlobalTech", 1100.0, 300);
//
//    warehouse.addShipment(std::move(shipment1));
//    warehouse.addShipment(std::move(shipment2));
//    warehouse.addShipment(std::move(shipment3));
//
//    std::cout << "New warehouse created with shipments." << std::endl;
//}
//
//
//int main() {
//    Warehouse warehouse;
//
//    char option;
//    std::cout << "Do you want to load an existing warehouse? (Y/N): ";
//    std::cin >> option;
//
//    if (option == 'Y' || option == 'y') {
//        try {
//            warehouse.loadFromJson("warehouse.json");
//            std::cout << "Warehouse loaded successfully." << std::endl;
//        }
//        catch (const std::exception& e) {
//            std::cerr << "Error loading warehouse: " << e.what() << std::endl;
//            std::cout << "No warehouses found. Do you want to create a new one? (Y/N): ";
//            std::cin >> option;
//            if (option == 'Y' || option == 'y') {
//                createNewWarehouse(warehouse);
//            }
//        }
//    }
//    else {
//        createNewWarehouse(warehouse);
//    }
//
//
//    while (true) {
//        std::cout << "Choose your role:" << std::endl;
//        std::cout << "1. Warehouse Manager" << std::endl;
//        std::cout << "2. Customer" << std::endl;
//        std::cout << "3. Exit" << std::endl;
//        int roleOption;
//        std::cin >> roleOption;
//
//        if (roleOption == 3) {
//            std::cout << "Exiting program." << std::endl;
//            break;
//        }
//
//        if (roleOption == 1) {
//            while (true) {
//                std::cout << "Welcome, Warehouse Manager!" << std::endl;
//                std::cout << "1. Fire worker" << std::endl;
//                std::cout << "2. Add Worker" << std::endl;
//                std::cout << "3. Generate Invoice" << std::endl;
//                std::cout << "4. Generate Receipt" << std::endl;
//                std::cout << "5. Apply Discounts" << std::endl;
//                std::cout << "6. Exit to Main Menu" << std::endl;
//
//                //TODO trzeba dodaæ opcje dodawania wykresów i napisaæ takie funkcje
//
//                int managerOption;
//                std::cin >> managerOption;
//
//                if (managerOption == 6) {
//                    break;
//                }
//
//                switch (managerOption) {
//                case 1: {
//                    warehouse.listWorkers();
//                    std::cout << "Enter the number of the worker to fire: ";
//                    size_t workerIndex;
//                    std::cin >> workerIndex;
//                    if (warehouse.fireWorker(workerIndex)) {
//                        std::cout << "Worker fired successfully." << std::endl;
//                    }
//                    else {
//                        std::cout << "Failed to fire worker." << std::endl;
//                    }
//                    break;
//                }
//                case 2: {
//                    std::string name, lastName;
//                    int age, experience;
//                    double salary;
//                    int post;
//
//                    std::cout << "Enter worker name: ";
//                    std::cin >> name;
//                    std::cout << "Enter worker last name: ";
//                    std::cin >> lastName;
//                    std::cout << "Enter worker age: ";
//                    std::cin >> age;
//                    std::cout << "Enter worker post (0 - Physical Labor, 1 - Warehouse Management): ";
//                    std::cin >> post;
//                    std::cout << "Enter worker salary: ";
//                    std::cin >> salary;
//                    std::cout << "Enter worker experience: ";
//                    std::cin >> experience;
//
//                    Worker worker(name, lastName, age, static_cast<Post>(post), salary, experience);
//                    warehouse.addWorker(std::make_unique<Worker>(worker));
//                    std::cout << "Worker added successfully." << std::endl;
//                    break;
//                }
//                case 3: {
//                    std::string invoiceNumber;
//                    std::cout << "Enter invoice number: ";
//                    std::cin >> invoiceNumber;
//
//                    Person seller("SellerName", "SellerLastName", 0);
//                    std::shared_ptr<Customer> customer = std::make_shared<Firm>("FirmName", "FirmLastName", 0, "Firm", "12345", "NASDAQ");
//                    std::string path = "invoice.pdf";
//
//                    auto transactions = warehouse.getTransactions();
//                    warehouse.generateInvoice(invoiceNumber, seller, customer, path, transactions);
//                    std::cout << "Invoice generated successfully." << std::endl;
//                    break;
//                }
//
//                case 4: {
//                    std::string paymentMethod;
//                    std::cout << "Enter payment method: ";
//                    std::cin >> paymentMethod;
//
//                    std::shared_ptr<Customer> customer = std::make_shared<PrivatePerson>("CustomerName", "CustomerLastName", 0);
//                    std::string path = "receipt.pdf";
//
//                    auto transactions = warehouse.getTransactions();
//                    warehouse.generateReceipt(paymentMethod, customer, path, transactions);
//                    std::cout << "Receipt generated successfully." << std::endl;
//                    break;
//                }
//                case 5: {
//                    double discountRate;
//                    int daysBeforeExpiry;
//
//                    std::cout << "Enter discount rate: ";
//                    std::cin >> discountRate;
//                    std::cout << "Enter number of days before expiry: ";
//                    std::cin >> daysBeforeExpiry;
//
//                    warehouse.applyDiscounts(discountRate, daysBeforeExpiry);
//                    std::cout << "Discounts applied successfully." << std::endl;
//                    break;
//                }
//                default: {
//                    std::cout << "Invalid option for Warehouse Manager." << std::endl;
//                    break;
//                }
//                }
//            }
//        }
//        else if (roleOption == 2) {
//            while (true) {
//                std::cout << "Welcome, Customer!" << std::endl;
//                std::cout << "1. Search Product by Name" << std::endl;
//                std::cout << "2. Search Product by Manufacturer" << std::endl;
//                std::cout << "3. Search Product by Expiry Date" << std::endl;
//                std::cout << "4. Search Product by Type" << std::endl;
//                std::cout << "5. View Purchase History" << std::endl;
//                std::cout << "6. Exit to Main Menu" << std::endl;
//
//                int customerOption;
//                std::cin >> customerOption;
//
//                if (customerOption == 6) {
//                    break;
//                }
//
//                switch (customerOption) {
//                case 1: {
//                    std::string productName;
//                    std::cout << "Enter the name of the product: ";
//                    std::cin >> productName;
//                    auto products = warehouse.searchByName(productName);
//                    break;
//                }
//                case 2: {
//                    std::string manufacturerName;
//                    std::cout << "Enter the manufacturer name: ";
//                    std::cin >> manufacturerName;
//                    auto products = warehouse.searchByManufacturer(manufacturerName);
//                    break;
//                }
//                case 3: {
//                    std::time_t expiryDate;
//                    std::cout << "Enter the expiry date (as timestamp): ";
//                    std::cin >> expiryDate;
//                    auto products = warehouse.searchByExpiryDate(expiryDate);
//                    break;
//                }
//                case 4: {
//                    int productType;
//                    std::cout << "Enter the product type (1 - Perishable, 2 - NonPerishable, 3 - Electronics, 4 - Apparel): ";
//                    std::cin >> productType;
//                    ProductType type = static_cast<ProductType>(productType - 1);
//                    auto products = warehouse.searchByType(type);
//                    break;
//                }
//                case 5: {
//                    auto transactions = warehouse.getTransactions();
//                    break;
//                }
//                default: {
//                    std::cout << "Invalid option for Customer." << std::endl;
//                    break;
//                }
//                }
//            }
//        }
//        else {
//            std::cout << "Invalid role option. Please choose again." << std::endl;
//        }
//    }
//
//    char option;
//    std::cout << "Do you want to save the warehouse to a JSON file? (Y/N): ";
//    std::cin >> option;
//
//    if (option == 'Y' || option == 'y') {
//        try {
//            warehouse.saveToJson("warehouse.json");
//            std::cout << "Warehouse saved to 'warehouse.json'." << std::endl;
//        }
//        catch (const std::exception& e) {
//            std::cerr << "Error saving warehouse to JSON: " << e.what() << std::endl;
//        }
//    }
//
//    return 0;
//}