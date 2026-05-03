#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H
#include <map>
#include <memory>
#include <mutex>

#include "Product.h"
class InventoryManager
{
    public:
        /**
            Constructs an InventoryManager object with the following details.
            @param a mapping with the integer key = productID and value = pointer to the product object to be used
        */
        InventoryManager(std::map<int, std::shared_ptr<Product>> productMap);

        ~InventoryManager();

        /**

          * Adds new product to inventory
          * @param product Shared pointer to the product object to be added
          * @return True if product is successfully added, false otherwise
        */
        bool addNewProduct(std::shared_ptr<Product> product);


        /**

          * remove product from the inventory by id
          * @param product id
          * @return True if product is successfully removed, false otherwise

        */
        bool removeProduct(int productId);

        /**

          * searches for a product using productId
          * @param product id
          * @return shared pointer to the product object, null pointer otherwise

        */
        std::shared_ptr<Product> searchProductById(int productId) const;

        /**

          * displays product by price in ascending order

        */
        void sortAndDisplayProductByPrice();

        /**

          * displays product by quantity in ascending order

        */
        void sortAndDisplayProductByQuantity();

        /**

          * displays product in the inventory

        */
        bool displayAllProducts() const;

        /**

          * processes orders
          * @param product id, quantity requested of the product
          * @return True if order is successfully processed, False otherwise
        */
        bool processOrder(int productId, int quantityRequested);

        /**

          * update product using productID and quantity
          * @param productID, quantity
          * @return bool, if product updates true, otherwise

        */

        bool updateProduct(int productID, int newQuant);


        /**

          * Removes the Product using product name
          * @param name
          * @return bool, true if removed, otherwise

        */

        bool removeProduct(const std::string &name);

        /**
            Loads all information about the products in productMap to ProductData.txt
            @return 0 - successfull
            @return 1 - failed
            @return 2 - file not found
        */
        int storeMap();

        /**
            Loads all information about the products in ProductData.txt to productMap
            @return 0 - successfull
            @return 1 - failed
            @return 2 - file not found
        */
        int loadMap();

    private:
        std::map<int, std::shared_ptr<Product>> productMap;
        mutable std::mutex mapMutex;
};

#endif // INVENTORYMANAGER_H
