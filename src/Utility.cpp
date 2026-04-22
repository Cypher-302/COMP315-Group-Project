#include "../include/Utility.h"
#include "../include/Product.h"

#include <iostream>
#include <thread>
#include <ctime>
#include <chrono>
#include <vector>
#include <string>

namespace Utility
{
    void pause(int mSec){
        std::this_thread::sleep_for(std::chrono::milliseconds(mSec));
    }

    void printChars(char c, int reps){
        for(int i=1; i< reps; i++){
            std::cout<<c;
        }
        std::cout<<"\n";
    }

    void printChars(char c, char sep, int reps){
        for(int i=1; i< reps; i++){
            std::cout<<c<< sep;
        }
        std::cout<< "\n";
    }

    void printRep(char c, char sep, int reps){
        for(int i=1; i< reps; i++){
            std::cout<<c<< sep;
        }
    }

    void line(){
        std::cout<<"\n";
        printChars('�','�',65); // from reps
        std::cout<<"\n";
    }

    void fillString(std::string &str){
        int spaces = 20 - str.length();
        for(int i=spaces; i > 0; i--){
            str +=" ";
        }
    }

    /*void displayAllProds(std::vector<Product> &prods){
        std::string prodID, prodName, price, quantity;

        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
        printRep(' ',' ',14 -1); std::cout<<"| Product ID          | Product Name        | Price               | Quantity            | Final Price          |"; std::cout<<"\n";
        printRep(' ',' ',14); printRep('_','_',55);std::cout<<"\n";
        for(Product p: prods){
            prodID = to_string(p.getId());
            prodName = p.getName();
            quantity = to_string(p.getQuant());
            price = to_string(p.calculateFinalPrice());
            //ensure size
            fillString(&prodID);fillString(&prodName);fillString(&quantity);fillString(&price);
            // print row
            printRep(' ',' ',14 -1);
            std::cout<<"| "<<prodID<<"| "<<prodName<<"| "<<price<<"| "<<quantity<<"|\n";
            printRep(' ',' ',14); printRep('_','_',44);std::cout<<"\n";

        }
    }*/
}

