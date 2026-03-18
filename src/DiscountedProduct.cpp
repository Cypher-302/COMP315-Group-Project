#include "../include/DiscountedProduct.h"
#include <iostream>
#include <string>

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

void DiscountedProduct::display(){
     std::cout << "ID: " << getId()
             << ", Name: " << getName()
             << ", Discount: " << getDiscount()
             << ", Price: " << getPrice()
             << ", Quantity: " << getQuant()
             << ", Final Price: " << calculateFinalPrice() << std::endl;
}

