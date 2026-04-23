#ifndef PRODUCT_H
#define PRODUCT_H

#include <mutex>
#include <string>
#include <atomic>

class Product
{
private:
    std::string name;
    double price;
    int productID;
    int quantity;
    mutable std::mutex productMutex;
    std::atomic<bool> active; // A boolean flag that represents whether a product is still valid/ in-use


public:
    /**
        Constructs the Product object with the following details.
        @param the_name     -
        @param the_price    -
        @param id           -
        @param the_quantity -
    */
    Product(std::string the_name, double the_price, int id, int the_quantity);

    // Destructor
    virtual ~Product();

    /**
        Gets the price of this product
        @return the_price
     */
    double getPrice() const;

    /**
        Gets the name of this product
        @return the_name
     */
    std::string getName() const;

    /**
        Gets the number of items available of this product
        @return the_quantity
    */
    int getQuant() const;

    /**
        Gets the Id of this product
        @return id
    */
    int getId() const;

    /**
     Returns a reference to the existing mutex.
     Marked const because the mutex is mutable.
     */
    std::mutex& getProductMutex() const;

    /**
        Returns wheteher a product is still valid.
        @return active 
     */
    std::atomic<bool> getActive() const;

    /**
        set the status of the product to true 
        @param active 
     */
    void setActive(std::atomic<bool> active);

    /**
        Updates the name of this product
        @param the_name
    */
    void setName(std::string the_name);

    /**
        Updates the number of items available of this product
        @param the_quantity
    */
    void setQuant(int number);

    /**
        Updates the original price of this product
        @param the_price
     */
    void setPrice(double the_price);

    /**
        Updates the ID of this product
        @param id
    */
    void setID(int the_ID);

    /**
        Calculates and returns the original rice of this product
        @return the_price
    */
    virtual double calculateFinalPrice();

    /**
        Displays all the details of this product
    */
    virtual void display();

    /**
        Displays the tabulated version of all the product's details
    */
    virtual void displayTab();

    /**
        Returns the type of the product
        @return Product
    */
    virtual std::string getType() const;


};

#endif // PRODUCT_H
