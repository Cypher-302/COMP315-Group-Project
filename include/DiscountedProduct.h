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
        @param the_name     - The string identifier representing the name of the product.
        @param the_price    - The numerical value representing the unit cost of the product.
        @param id           - The unique integer used to identify the product instance.
        @param the_quantity - The integer count of the product units currently in stock.
        @param the_discount - The decimal value representing the reduction applied to the base price.
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

    /**
        Displays the tabulated version of all the product's details
    */
    void displayTab() override;

    /**
        Returns the type of the product
        @return DiscountedProduct
    */
    std::string getType() const;
};

#endif // DISCOUNTEDPRODUCT_H
