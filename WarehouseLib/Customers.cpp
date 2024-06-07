#include "Customers.h"
#include <sstream>
#include <stdexcept>

// DONE

Customer::Customer(const std::string& name, const std::string& lastname, int age)
    : Person(name, lastname, age) {}

void Customer::addPurchase(const Product& product) {
    purchaseHistory.push_back(product);
}

std::string Customer::getPurchaseHistory() const {
    std::ostringstream oss;
    oss << "Purchase history:\n";
    for (const auto& product : purchaseHistory) {
        oss << "Product name: " << product.name << "\n"
            << "Price: " << product.price << "\n"
            << "Country: " << product.country << "\n";
    }
    return oss.str();
}

double Customer::calculateDiscount() const {
    return 0.0;
}

PrivatePerson::PrivatePerson(const std::string& name, const std::string& lastname, int age)
    : Customer(name, lastname, age) {}

void PrivatePerson::addPreference(const Item& preference) {
    purchasePreferences.push_back(preference);
}

Item PrivatePerson::getPreference(ProductType type) const {
    for (const auto& item : purchasePreferences) {
        if (item.getType() == type) {
            return item;
        }
    }
    throw std::runtime_error("No preference found for the given product type.");
}

double PrivatePerson::calculateDiscount() const {
    int purchaseAmount = purchaseHistory.size();

    if (purchaseAmount > 50) {
        return 0.3;
    }
    else if (purchaseAmount > 35) {
        return 0.2;
    }
    else if (purchaseAmount > 20) {
        return 0.1;
    }
    else if (purchaseAmount > 10) {
        return 0.05;
    }

    return 0.0;
}

Firm::Firm(const std::string& name, const std::string& lastname, int age,
    const std::string& firmName, const std::string& id, const std::string& exchange)
    : Customer(name, lastname, age), firmName(firmName), id(id), exchange(exchange) {}

std::string Firm::getFirmName() const {
    return firmName;
}

std::string Firm::getId() const {
    return id;
}

std::string Firm::getExchange() const {
    return exchange;
}

double Firm::calculateDiscount() const {
    double summaryValue = 0;
    for (const auto& purchase : purchaseHistory) {
        summaryValue += purchase.price;
    }

    if (summaryValue > 100000) {
        return 0.5;
    }
    else if (summaryValue > 80000) {
        return 0.4;
    }
    else if (summaryValue > 60000) {
        return 0.3;
    }
    else if (summaryValue > 40000) {
        return 0.2;
    }
    else if (summaryValue > 20000) {
        return 0.1;
    }
    else if (summaryValue > 10000) {
        return 0.05;
    }

    return 0.0;
}
