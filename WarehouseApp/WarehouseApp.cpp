#include <iostream>
#include <memory>
#include <ctime>
#include "../WarehouseLib/DataTransfer.h"
#include "../WarehouseLib/Warehouse.h"
#include "../WarehouseLib/Items.h"
#include "../WarehouseLib/Workers.h"

int main() {
    //Manager manager1("John", "Doe", 45, 50000, 10);
    //Worker worker1("Jane", "Smith", 30, Post::PhysicalLabor, 30000, 5);

    //auto now = std::time(nullptr);
    //std::unique_ptr<Product> product1(new Product(manager1, worker1, "Product1", 100.0, 20.0, "USA", now + 3600 * 24 * 30, 1000, ProductType::Perishable));
    //std::unique_ptr<Product> product2(new Product(manager1, worker1, "Product2", 200.0, 40.0, "Canada", now + 3600 * 24 * 60, 2000, ProductType::NonePerishable));
    //std::unique_ptr<Product> product3(new Product(manager1, worker1, "Product3", 300.0, 60.0, "UK", now + 3600 * 24 * 90, 3000, ProductType::Electronics));
    //std::unique_ptr<Product> product4(new Product(manager1, worker1, "Product4", 400.0, 80.0, "Germany", now + 3600 * 24 * 120, 4000, ProductType::Apparel));
    //std::unique_ptr<Product> product5(new Product(manager1, worker1, "Product5", 500.0, 100.0, "France", now + 3600 * 24 * 150, 5000, ProductType::Perishable));

    //Warehouse warehouse;
    //warehouse.addProduct(std::move(product1));
    //warehouse.addProduct(std::move(product2));
    //warehouse.addProduct(std::move(product3));
    //warehouse.addProduct(std::move(product4));
    //warehouse.addProduct(std::move(product5));

    //DataTransfer::saveToJson(warehouse, "warehouse.json");

    //std::cout << "Produkty zosta³y zapisane do pliku warehouse.json" << std::endl;

    return 0;
}
