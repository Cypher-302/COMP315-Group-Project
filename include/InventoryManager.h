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
            Constructs an Order object with the following details.
            @param a mapping with the integer key = productID and value = pointer to the product object to be used
        */
        InventoryManager(std::map<int, std::shared_ptr<Product>> productMap);

        ~InventoryManager();

        /**

          * Adds new product to inventory
          * @param shared pointer to the product object to be added

        */
        void addNewProduct(std::shared_ptr<Product> product);


        /**

          * remove product from the inventory by id
          * @param product id

        */
        void removeProduct(int productId);

        /**

          * searches for a product using productId
          * @param product id
          * @return shared pointer to the product object

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
        void displayAllProducts() const;

        /**

          * processes orders
          * @param product id, quantity requested of the product
          * @return bool
        */
        bool processOrder(int productId, int quantityRequested);

    private:
        std::map<int, std::shared_ptr<Product>> productMap;
        mutable std::mutex mapMutex;
};

#endif // INVENTORYMANAGER_H
