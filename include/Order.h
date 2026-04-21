#include <string>
using namespace std;

class Order {
private:
    int orderID, productID;
    int quantityRequested;
    bool orderStatus;

public:
    /**
        Constructs an Order object with the following details.
        @param oID  - The unique integer identifier for the order record.
        @param pID  - The unique integer identifier for the associated product.
        @param qR   - The integer count of product units requested in the order.
        @param oS   - The boolean flag representing the fulfillment status of the order.
    */
    Order(int oID, int pID, int qR, bool oS);

    // Destructor
    ~Order();

    /**
        Updates the order ID of this order.
        @param oID
    */
    void setOrderID(int oID);

    /**
        Updates the product ID of a product in the order.
        @param pID
    */
    void setProductID(int pID);

    /**
        Updates the quantity of product the user requested.
        @param qR
    */
    void setQuantityRequested(int qR);

    /**
        Updates the status of this order.
        @param oS
    */
    void setOrderStatus(bool oS);

    /**
        Gets the ID of this order.
        @return orderID
    */
    int getOrderID();

    /**
        Gets the ID of a specified product in this order
        @return productID
    */
    int getProductID();

    /**
        Gets the user requested quantity of a product in this order.
        @return quantityRequsted
    */
    int getQuantityRequested();

    /**
        Gets the status of this order.
        @return orderStatus
    */
    bool getOrderStatus();

};
