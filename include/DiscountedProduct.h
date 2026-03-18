#ifndef DISCOUNTEDPRODUCT_H
#define DISCOUNTEDPRODUCT_H

#include "Product.h"
#include <string>
/*
this class declares the methods and attributes to be used when applying a discount to a product.

*/

class DiscountedProduct : public Product
{
private:
    double discount;

public:
    /**
        Constructs the DiscountedProduct object with the following details.
        @param the_name     -
        @param the_price    -
        @param id           -
        @param the_quantity -
        @param the_discount -
    */
    DiscountedProduct(std::string the_name, double the_price, int id, int the_quantity, double the_discount);

    // Destructor
    ~DiscountedProduct();


    /**
        Gets the discount applied on this product
        @return the_discout
     */
    double getDiscount() const;

    /**
        Updates the discount applied on this product
        @param the_discount

    */
    void setDiscount(double the_discount);


    /**
        Calculates and returns the final price of the product with the discount applied
        @return the_price
     */
    double calculateFinalPrice() override;
    void display() override;

};

#endif // DISCOUNTEDPRODUCT_H
