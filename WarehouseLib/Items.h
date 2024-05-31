#pragma once
#include <string>
#include <vector>
#include "Workers.h"
#include <ctime>


enum class ProductType {
	Perishable,
	NonePerishable,
	Electronics,
	Apparel
};

class Item {
private:
	std::string name;
	double price;
	ProductType type;
	double tax;
public:
	Item(const std::string& name, double price, const ProductType type, double tax);

	std::string getName() const;
	double getPrice() const;
	ProductType getType() const;
	double getTax() const;
};

struct ShipmentDetail {
	Item item;
	int quantinty;
	ShipmentDetail(const Item& item, int quantity);
};

class Shipment {
	//TODO
private:
	std::vector<ShipmentDetail> items;
	Manager receivingManager;
	Worker storageWorker;
	std::string deliveryCompany;
	double totalcost;
public:
	Shipment(const std::vector<ShipmentDetail>& items, const Manager& receivingManager, const Worker& storageWorker, const std::string& deliveryCompany);
	const std::vector<ShipmentDetail>& getProducts();
	Manager getReceivingManager();
	Worker getStorageWorker();
	std::string getDeliveryCompany();
	double getTotalCost();
	void addProducts();
};

class Product {
private:
	Manager receivingManager;
	Worker storageWorker;
	std::time_t sale_date;
	bool is_sold;

public:
	ProductType type;
	std::string name;
	double price;
	double tax;
	std::string country;
	std::time_t validity_term;
	std::time_t sale_date;
	int weight; //grams
	Product(const Manager& recManager, const Worker& storWorker, const std::string& name, double price, double tax, const std::string& country, std::time_t validity, int weight, ProductType type);
	std::time_t getSaleDate() const;
	void setSaleDate(std::time_t newSaleDate);
	bool isAvailable() const;
};