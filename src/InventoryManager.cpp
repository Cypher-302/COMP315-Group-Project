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
  * @param shared pointer to the product object to be added
*/
void InventoryManager::addNewProduct(shared_ptr<Product> product) {

    std::lock_guard<std::mutex> lockMap(mapMutex);

    int id = product->getId();
    if(productMap.find(id) == productMap.end()) {
        productMap[id] = product;
    } else {
        cout << "Product with this ID already exists" << endl;
    }
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

