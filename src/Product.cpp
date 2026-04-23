#include "../include/Product.h"
#include "../include/Utility.h"

#include <iostream>
#include <string>

using namespace Utility;

Product::Product(std::string the_name, double the_price, int id, int the_quantity)
            :name(the_name), price(the_price), productID(id) ,quantity(the_quantity){

            }

Product::~Product(){}

double Product::getPrice() const{
    return price;
}

std::string Product::getName() const {
    return name;
}

int Product::getQuant() const{
    return quantity;
}

int Product::getId() const{
    return productID;
}

std::mutex& Product::getProductMutex() const
{
    return productMutex;
}

std::atomic<bool> Product::getActive() const {
    return true;
}
void Product::setActive(std::atomic<bool> active){
    active = true;
}

void Product::setName(std::string the_name){
    name = the_name;
}

void Product::setQuant(int num){
    if (num >= 0){
        quantity = num;
    }else{
        std::cout << "Quantity can not be negative" << std::endl;
    }
}


void Product::setPrice(double pri){
    if (pri >= 0){
        price = pri;
    }else{
        std::cout << "Price can not be negative" << std::endl;
    }
}


void Product::setID(int id){
    if (id >= 0){
        productID = id;
    }else{
        std::cout << "Product ID can not be negative" << std::endl;
    }
}

 std::string Product::getType() const {
        return "Product";
}

double Product::calculateFinalPrice(){
    return price;
}

void Product::display(){
     std::cout << "ID: " << getId()
             << ", Name: " << getName()
             << ", Price: R" << getPrice()
             << ", Quantity: " << getQuant()
             << ", Final Price: R" << calculateFinalPrice() << std::endl;

}
void Product::displayTab(){
    std::string prodID, prodName, price, quantity, finalPrice;

            prodID = std::to_string(getId());
            prodName = getName();
            quantity = std::to_string(getQuant());
            price = std::to_string(getPrice());
            finalPrice = std::to_string(calculateFinalPrice());
            //ensure size
            fillString(prodID);fillString(prodName);fillString(quantity);fillString(price);
            fillString(finalPrice);
            // print row
            printRep(' ',' ',14 -1);
            std::cout<<"| "<<prodID<<"| "<<prodName<<"| "<<price<<"| "<<quantity<<"| "<<finalPrice<<"|\n";
}

