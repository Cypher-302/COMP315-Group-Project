#ifndef TAXABLEPRODUCT_H
#define TAXABLEPRODUCT_H

#include "Product.h"
#include <string>

class TaxableProduct : public Product
{
private:
    double tax;

public:

    /**
    Constructs a TaxableProduct object with the following details.
    @param the_name     -
    @param the_price    -
    @param id           -
    @param the_quantity -
    @param the_tax      -

    */

    TaxableProduct(std::string the_name, double the_price, int id, int the_quantity, double the_tax);
    ~TaxableProduct();


    /** *
        Gets the tax applied on this product.
        @return the_tax
    */
    double getTax () const;

    /**
        updates the tax applied on this product.
        @param the_tax
    */
    void setTax(double the_tax);

    /**
        Calculates and returns the total price of the product with tax included
        @return price
     */
    double calculateFinalPrice() override;

    /**
        Displays the statement/details of the product
     */
    void display() override;
    /**
        Displays the tabulated version of all the product's details
    */
    void displayTab() override;
};

#endif // TAXABLEPRODUCT_H
