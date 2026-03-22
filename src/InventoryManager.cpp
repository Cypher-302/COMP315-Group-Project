#include "../include/InventoryManager.h"
#include <iostream>
using namespace std;

/**
  * Constructs an Order object with the following details.
  * @param a mapping with the integer key = productID and value = pointer to the product object to be used
*/
InventoryManager::InventoryManager(map<int, shared_ptr<Product>> productMap) : productMap(productMap) {}

/**
  * Adds new product to inventory
  * Thread safe
  * @param product Shared pointer to the product object to be added
  * @return True if product is successfully added, false otherwise
*/
bool InventoryManager::addNewProduct(shared_ptr<Product> product) {

    if(!product) {
        return false;
    }

    std::lock_guard<std::mutex> lockMap(mapMutex);

    int id = product->getId();
    if(productMap.find(id) == productMap.end()) {
        productMap.insert({id, product});
        return true;
    }

    return false;
}

/**
  * remove product from the inventory by id
  * @param product id
  * @return True if product is successfully removed, false otherwise
*/
bool InventoryManager::removeProduct(int productId) {

    std::lock_guard<std::mutex> lockMap(mapMutex);

    auto it = productMap.find(productId);

    if(it != productMap.end()) {
        productMap.erase(it);
        return true;
    }

    return false;
}

/**
  * searches for a product using productId
  * @param product id
  * @return shared pointer to the product object, null pointer otherwise
*/
shared_ptr<Product> InventoryManager::searchProductById(int productId) const {

    std::lock_guard<std::mutex> lockMap(mapMutex);

    auto it = productMap.find(productId);

    if(it != productMap.end()) {
        return it->second;
    }

    return nullptr;
}

/**
  * displays all product if available
*/
void InventoryManager::displayAllProducts() const {

    std::lock_guard<std::mutex> lock(mapMutex);

    if(productMap.empty()) {
        cout << "No products available";
        return;
    }

    for(auto p : productMap) {
        p.second->display();
    }
}

InventoryManager::~InventoryManager(){}

