#include "../include/DiscountedProduct.h"
#include <iostream>
#include <string>
#include "../include/Utility.h"

using namespace Utility;
DiscountedProduct::DiscountedProduct(std::string the_name, double the_price, int id, int the_quantity, double the_discount)
                        :Product(the_name, the_price, id, the_quantity){
                            discount = the_discount;
                        }

DiscountedProduct::~DiscountedProduct(){

}


double DiscountedProduct::getDiscount() const{
    return discount;
}

void DiscountedProduct::setDiscount(double the_discount){
    discount = the_discount;
}

double DiscountedProduct::calculateFinalPrice(){
    double first = discount / 100.00;
    double second = first * getPrice();
    return getPrice() - second;
}

 std::string DiscountedProduct::getType() const {
        return "DiscountedProduct";
}


void DiscountedProduct::display(){
     std::cout << "ID: " << getId()
             << ", Name: " << getName()
             << ", Discount: " << getDiscount()
             << "% , Price: R" << getPrice()
             << ", Quantity: " << getQuant()
             << ", Final Price: R" << calculateFinalPrice() << std::endl;
}

void DiscountedProduct::displayTab(){
    std::string prodID, prodName, price, quantity,finalPrice;
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

