#include "../include/InventoryManager.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
  * Thread safe
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
  * Thread safe
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
  * Thread safe
*/
bool InventoryManager::displayAllProducts() const {

    std::lock_guard<std::mutex> lock(mapMutex);

    if(productMap.empty()) {
        cout << "No products available";
        return false;
    }

    int center = 30;
    cout << string(center, ' ');

    for(auto p : productMap) {
        p.second->display();
    }
    return true;
}

/**
  * processes orders
  * Thread safe
  * @param product id, quantity requested of the product
  * @return true if order is successfully processed, false otherwise
*/
bool InventoryManager::processOrder(int productId, int quantityRequested) {

    if(quantityRequested <= 0) return false;

    std::lock_guard<std::mutex> lock(mapMutex);

    auto it = productMap.find(productId);

    if(it != productMap.end()) {

        int quantity = it->second->getQuant();

        if(quantity >= quantityRequested) {

            it->second->setQuant(quantity - quantityRequested);
            return true;
        }
    }

    return false;
}

/**

* displays product by price in ascending order

*/
void InventoryManager::sortAndDisplayProductByPrice(){

    std::lock_guard<std::mutex> lock(mapMutex);

    std::vector<std::shared_ptr<Product>> holder;
if(productMap.empty()){cout<<"No products in inventory to be displayed";}else{

    for(auto& e: productMap){
        holder.push_back(e.second);
    }
    std::sort(holder.begin(),holder.end(), [](const std::shared_ptr<Product>& a,const std::shared_ptr<Product>& b)
              {
                  return (a->getPrice())< (b->getPrice());

              } );
    for(std::shared_ptr<Product>& p: holder){
        p->display();
    }
}//end of ifelse
}

/**

* displays product by quantity in ascending order

*/
void InventoryManager::sortAndDisplayProductByQuantity(){
    std::lock_guard<std::mutex> lock(mapMutex);

    std::vector<std::shared_ptr<Product>> holder;
if(productMap.empty()){cout<<"No products in inventory to be displayed";}else{

    for(auto& e: productMap){
        holder.push_back(e.second);
    }
    std::sort(holder.begin(),holder.end(), [](const std::shared_ptr<Product>& a,const std::shared_ptr<Product>& b)
              {
                  return (a->getQuant())< (b->getQuant());

              } );
    for(std::shared_ptr<Product>& p: holder){
        p->display();
    }
}//end of ifelse

}



bool InventoryManager::updateProduct(int productID, int newQuantity) {
    if(newQuantity < 0) return false;

    std::lock_guard<std::mutex> lock(mapMutex);

    auto it = productMap.find(productID);

    if(it != productMap.end() && it->second) {
        it->second->setQuant(newQuantity);
        return true;
    }

    return false;
}



InventoryManager::~InventoryManager(){}

