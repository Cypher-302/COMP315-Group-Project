#include "../include/DiscountedProduct.h"
#include "../include/TaxableProduct.h"
#include "../include/InventoryManager.h"
#include "../include/Utility.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
<<<<<<< HEAD
#include "../include/DiscountedProduct.h"
#include "../include/TaxableProduct.h"
=======
>>>>>>> 0196a8dae8e9dbc9dcdcc3fef27d6913b1eccc64
#include <sstream>
#include <thread>

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

    std::lock_guard<std::mutex> lock(mapMutex);

    auto it = productMap.find(productId);

    if(it != productMap.end()) {
        it->second->getActive() = true;
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
bool InventoryManager::processOrder(int productId, int quantityRequested)
{
    std::shared_ptr<Product> targetProduct = nullptr;

    { // structural lock to find the product pointer and release the map lock ASAP
        std::lock_guard<std::mutex> lock(mapMutex);
        auto it = productMap.find(productId);
        if (it != productMap.end())
        {
            targetProduct = it->second;
        }
    }

    // A static mutex to safely lock the std::cout stream across all threads,
    //  preventing race conditions for standard output
    static std::mutex coutMutex;

    if (targetProduct) // null check
    { // transactional lock to protect the specific product and print output
        std::lock_guard<std::mutex> productLock(targetProduct->getProductMutex());

        int currentStock = targetProduct->getQuant();

        if (quantityRequested < 0) // handle restocking
        {
            // subtracting a negative number adds it, so this still works:
            targetProduct->setQuant(currentStock - quantityRequested); // update stock

            std::lock_guard<std::mutex> printLock(coutMutex);
            std::cout << "[RESTOCK] Thread " << std::this_thread::get_id()
                      << " | Product: " << targetProduct->getName()
                      << " | Added: " << (-quantityRequested) // make positive for terminal output
                      << " | New Stock: " << targetProduct->getQuant() << std::endl;
            return true;
        }
        else if (currentStock >= quantityRequested) // handle successful purchases
        {
            targetProduct->setQuant(currentStock - quantityRequested); // update stock

            std::lock_guard<std::mutex> printLock(coutMutex);
            std::cout << "[SUCCESS] Thread " << std::this_thread::get_id()
                      << " | Product: " << targetProduct->getName()
                      << " | Requested: " << quantityRequested
                      << " | New Stock: " << targetProduct->getQuant() << std::endl;
            return true;
        }
        else // handle failed purchases
        {
            std::lock_guard<std::mutex> printLock(coutMutex);
            std::cout << "[FAILED]  Thread " << std::this_thread::get_id()
                      << " | Product: " << targetProduct->getName()
                      << " | Insufficient Stock (" << currentStock << ")" << std::endl;
            return false;
        }
    }

    std::lock_guard<std::mutex> printLock(coutMutex);
    std::cout << "[FAILED]  Thread " << std::this_thread::get_id()
              << " | Product ID " << productId << " not found." << std::endl;
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

int InventoryManager::loadMap()
{
    std::ifstream file("ProductData.txt");
    if(!file) return 1; // if file doesn't exist, safely return

    std::string line, word;
    while(std::getline(file, line))
    {
        if(line.empty()) continue; // skip empty lines to prevent crashes

        std::vector<string> hold; // automatically resets every line
        std::stringstream str(line);
        while(std::getline(str, word, '#'))
        {
            hold.push_back(word);
        }

        // ensure the line has the minimum required fields (Type, ID, Name, Quant, Price)
        if(hold.size() < 5) continue;

        try
        {
            int id = std::stoi(hold[1]);
            int quant = std::stoi(hold[3]);
            double price = std::stod(hold[4]);

            if(hold[0] == "Product")
            {
                addNewProduct(make_shared<Product>(hold[2], price, id, quant));
            }
            else if(hold[0] == "DiscountedProduct")
            {
                double discount = 10; // default value
                if(hold.size() >= 6) // ensure the 6th field (discount) exists
                {
                    discount = std::stod(hold[5]);
                }
                addNewProduct(make_shared<DiscountedProduct>(hold[2], price, id, quant, discount));
            }
            else if(hold[0] == "TaxableProduct")
            {
                double tax = 15; // default value
                // ensure the 6th field (tax) exists
                if(hold.size() >= 6)
                {
                    tax = std::stod(hold[5]);
                }
                addNewProduct(make_shared<TaxableProduct>(hold[2], price, id, quant, tax));
            }
        }
        catch(const std::exception& e)
        {
            // if stoi or stod fail (e.g., text instead of numbers), safely ignore the line
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }
    return 0;
}

InventoryManager::~InventoryManager(){}