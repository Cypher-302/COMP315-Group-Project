#include <string>
#include "../include/TaxableProduct.h"
#include <iostream>
#include "../include/Utility.h"

using namespace Utility;

TaxableProduct::TaxableProduct(std::string the_name, double the_price, int id, int the_quantity, double the_tax)
                    :Product(the_name, the_price, id, the_quantity){
                        tax = the_tax;

                    }

TaxableProduct::~TaxableProduct(){
}

double TaxableProduct::getTax() const{
    return tax;
}

void TaxableProduct::setTax(double the_tax){
    tax = the_tax;
}

double TaxableProduct::calculateFinalPrice(){
    double value = tax / 100.00;
    double store = getPrice() * value;
    return getPrice() + store;
}

void TaxableProduct::display(){
     std::cout << "ID: " << getId()
             << ", Name: " << getName()
             << ", Tax: " << getTax()
             << ", Price: " << getPrice()
             << ", Quantity: " << getQuant()
             << ", Final Price: " << calculateFinalPrice() << std::endl;
}
void TaxableProduct::displayTab(){
    std::string prodID, prodName, price, quantity;
            prodID = std::to_string(getId());
            prodName = getName();
            quantity = std::to_string(getQuant());
            price = std::to_string(calculateFinalPrice());
            //ensure size
            fillString(prodID);fillString(prodName);fillString(quantity);fillString(price);
            // print row
            printRep(' ',' ',14 -1);
            std::cout<<"| "<<prodID<<"| "<<prodName<<"| "<<price<<"| "<<quantity<<"|\n";
}

