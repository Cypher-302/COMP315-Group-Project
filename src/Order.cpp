#include "../include/Order.h"

#include <string>

Order::Order(int oID, int pID, int qR, bool oS) {
    orderID = oID;
    productID = pID;
    quantityRequested = qR;
    orderStatus = oS;
}

Order::~Order() {}

void Order::setOrderID(int oID) {
    if(oID != 0) {
        this->orderID = oID;
    }
}
void Order::setProductID(int pID) {
    if(pID != 0) {
        this->productID = pID;
    }
}

void Order::setQuantityRequested(int qR) {
    if(qR > 0) {
        this->quantityRequested = qR;
    }
}

void Order::setOrderStatus(bool oS) {
    this->orderStatus = oS;
}

int Order::getOrderID() const{
    return orderID;
}

int Order::getProductID() const{
    return productID;
}

int Order::getQuantityRequested() const{
    return quantityRequested;
}

bool Order::getOrderStatus() const{
    return orderStatus;
}
