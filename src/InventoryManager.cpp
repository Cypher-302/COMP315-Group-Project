#include "../include/InventoryManager.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Utility.h"
#include <fstream>
#include "DiscountedProduct.h"
#include "TaxableProduct.h"
#include <sstream>

using namespace Utility;

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


    // prepare table
        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
        printRep(' ',' ',14 -1); std::cout<<"| Product ID          | Product Name        | Price               | Quantity            | Final Price         |"; std::cout<<"\n";
        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
    for(auto p : productMap) {
        p.second->displayTab();

        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
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
    // prepare table
        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
        printRep(' ',' ',14 -1); std::cout<<"| Product ID          | Product Name        | Price               | Quantity            | Final Price          |"; std::cout<<"\n";
        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
    for(std::shared_ptr<Product>& p: holder){
        p->displayTab();

        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
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

    // prepare table
        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
        printRep(' ',' ',14 -1); std::cout<<"| Product ID          | Product Name        | Price               | Quantity            | Final Price          |"; std::cout<<"\n";
        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";

    for(std::shared_ptr<Product>& p: holder){
        p->displayTab();

        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
    }
}//end of ifelse

}



bool InventoryManager::updateProduct(int productID, int newQuantity) {
    if(newQuantity < 0) return false;

    std::lock_guard<std::mutex> lock(mapMutex);

    auto it = productMap.find(productID);

    if(it != productMap.end() && it->second) {
        it->second->setQuant((it->second->getQuant())+newQuantity);
        return true;
    }

    return false;
}
/*
    ProductData.txt format
    Type#ID#Name#Quant#Price#Tax or Discount
*/
int InventoryManager::storeMap(){
    std::ofstream file("ProductData.txt", std::ios::trunc);

    if(!file){return 1;}
    std::lock_guard<std::mutex> lock(mapMutex);

    for(auto& e: productMap){
        if(e.second->getType() == "Product"){

        file<<e.second->getType()<<"#"<<e.second->getId()<<"#"<<e.second->getName()<<"#"<<e.second->getQuant()<<"#"<<e.second->getPrice()<<endl;

        }else if(e.second->getType() == "DiscountedProduct"){
        auto dp = std::dynamic_pointer_cast<DiscountedProduct>(e.second);
        file<<e.second->getType()<<"#"<<e.second->getId()<<"#"<<e.second->getName()<<"#"<<e.second->getQuant()<<"#"<<e.second->getPrice()<<"#"<<dp->getDiscount()<<endl;

        }else{
        auto tp = std::dynamic_pointer_cast<TaxableProduct>(e.second);
        file<<e.second->getType()<<"#"<<e.second->getId()<<"#"<<e.second->getName()<<"#"<<e.second->getQuant()<<"#"<<e.second->getPrice()<<"#"<<tp->getTax()<<endl;

        }
    }
    return 0;
}

int InventoryManager::loadMap(){
    std::ifstream file("ProductData.txt");
    std::vector<string> hold;
    int quant,id;
    double price,discOrTax;
    if(!file){return 1;}



    std::string line, word;
    while(std::getline(file,line)){
        std::stringstream str(line);
        while(std::getline(str,word,'#')){
            hold.push_back(word);
        }

        //
        quant = std::stoi(hold[3]);
        price =std::stod(hold[4]);
        id = std::stoi(hold[1]);

        if(hold[0]=="Product"){
            addNewProduct(make_shared<Product>(hold[2], price, id, quant));

        }else if(hold[0]=="DiscountedProduct"){
            discOrTax = std::stod(hold[5]);
            addNewProduct(make_shared<DiscountedProduct>(hold[2], price, id, quant,discOrTax));

        }else{
            discOrTax = std::stod(hold[5]);
            addNewProduct(make_shared<TaxableProduct>(hold[2], price, id, quant, discOrTax));
        }
        hold.clear();

    }


    return 0;
}

InventoryManager::~InventoryManager(){}

