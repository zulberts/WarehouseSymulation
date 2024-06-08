//#include "Transactions.h"
//#include <algorithm>
//#include <iomanip>
//
////DONE
//
//Transaction::Transaction(const Product& product, int quantity, double summaryPrice, const Worker& worker, std::shared_ptr<Customer> customer)
//    : product(product), quantity(quantity), summaryPrice(summaryPrice), worker(worker), customer(std::move(customer)), canceled(false) {
//    setTransactionTime();
//}
//
//double Transaction::calculateTax(double taxRate) const {
//    return quantity * summaryPrice * taxRate;
//}
//
//double Transaction::calculateDiscount(double discountRate) const {
//    return quantity * summaryPrice * discountRate;
//}
//
//void Transaction::cancel() {
//    canceled = true;
//}
//
//bool Transaction::isCanceled() const {
//    return canceled;
//}
//
//int Transaction::getQuantity() const {
//    return quantity;
//}
//
//std::time_t Transaction::getTransactionTime() const {
//    return transactionTime;
//}
//
//const Product& Transaction::getProduct() const {
//    return product;
//}
//
//std::shared_ptr<Customer> Transaction::getCustomer() const {
//    return customer;
//}
//
//double Transaction::getSummaryPrice() const {
//    return summaryPrice;
//}
//
//const Worker& Transaction::getWorker() const {
//    return worker;
//}
//
//void Transaction::setTransactionTime() {
//    transactionTime = std::time(nullptr);
//}
//
//void TransactionRegister::addTransaction(std::unique_ptr<Transaction> transaction) {
//    if (!transaction->isCanceled()) {
//        transactions.push_back(std::move(transaction));
//    }
//    else {
//        canceledTransactions.push_back(std::move(transaction));
//    }
//}
//
//void TransactionRegister::removeCanceledTransactions() {
//    transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
//        [](const std::unique_ptr<Transaction>& t) { return t->isCanceled(); }), transactions.end());
//}
//
//void TransactionRegister::restoreTransaction(std::unique_ptr<Transaction> transaction) {
//    if (transaction->isCanceled()) {
//        auto it = std::find_if(canceledTransactions.begin(), canceledTransactions.end(),
//            [&transaction](const std::unique_ptr<Transaction>& t) { return t.get() == transaction.get(); });
//        if (it != canceledTransactions.end()) {
//            transactions.push_back(std::move(*it));
//            canceledTransactions.erase(it);
//        }
//    }
//}
//
//std::vector<Transaction*> TransactionRegister::filterByDate(std::time_t from, std::time_t to) const {
//    std::vector<Transaction*> result;
//    for (const auto& t : transactions) {
//        if (t->getTransactionTime() >= from && t->getTransactionTime() <= to) {
//            result.push_back(t.get());
//        }
//    }
//    return result;
//}
//
//std::vector<Transaction*> TransactionRegister::filterByCustomer(const std::shared_ptr<Customer>& customer) const {
//    std::vector<Transaction*> result;
//    for (const auto& t : transactions) {
//        if (t->getCustomer()->getName() == customer->getName()) {
//            result.push_back(t.get());
//        }
//    }
//    return result;
//}
//
//std::map<std::string, int> TransactionRegister::mostFrequentlySoldProducts() const {
//    std::map<std::string, int> products;
//    for (const auto& transaction : transactions) {
//        products[transaction->getProduct().name] += transaction->getQuantity();
//    }
//    return products;
//}
//
//const std::vector<std::unique_ptr<Transaction>>& TransactionRegister::getCanceledTransactions() const {
//    return canceledTransactions;
//}
//
//const std::vector<std::unique_ptr<Transaction>>& TransactionRegister::getTransactions() const {
//    return transactions;
//}
