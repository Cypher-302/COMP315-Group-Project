#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include "include/Product.h"
#include "include/DiscountedProduct.h"
#include "include/TaxableProduct.h"
#include "include/InventoryManager.h"
using namespace std;

/**
    Sleeps\Pauses program for an amount of time
    @param mSec - duration in milliseconds
*/
void pause(int mSec){
    this_thread::sleep_for(chrono::milliseconds(mSec));
}

/**
    Prints a character a repeated number of times, plus new line
    @param c - the character
    @param reps - number of repetitions
*/
void printChars(char c, int reps){
    for(int i=1; i< reps; i++){
        cout<<c;
    }
    cout<<"\n";
}

/**
    Prints a character with seperators a repeated number of times, plus new line
    @param c - the character
    @param sep - seperating character
    @param reps - number of repetitions
*/
void printChars(char c, char sep, int reps){
    for(int i=1; i< reps; i++){
        cout<<c<< sep;
    }
    cout<< "\n";
}

/**
    Prints a character with seperators a repeated number of times
    @param c - the character
    @param sep - seperating character
    @param reps - number of repetitions
*/
void printRep(char c, char sep, int reps){
    for(int i=1; i< reps; i++){
        cout<<c<< sep;
    }
}
/**
    Draws a line of arrows across console
*/
void line(){
    cout<<"\n";
    printChars('«','»',65); // from reps
    cout<<"\n";
}

/**
    Apends spaces to strings less than 20 chars
    @param str - input string
*/
void fillString(string *str){
    int spaces = 20 - (*str).length();
    for(int i=spaces; i > 0; i--){
        *str +=" ";
    }
}
/**
    Displays information of all products in a table format
    @param prods - a pointer to the vector of products
*/
void displayAllProds(vector<Product> *prods){
    string prodID, prodName,price,quantity;

    printRep(' ',' ',14); printRep('_','_',55);cout<<"\n";
    printRep(' ',' ',14 -1); cout<<"| Product ID          | Product Name        | Price               | Quantity            | Final Price          |";cout<<"\n";
    printRep(' ',' ',14); printRep('_','_',55);cout<<"\n";
    for(Product p: *prods){
        prodID = to_string(p.getId());
        prodName = p.getName();
        quantity = to_string(p.getQuant());
        price = to_string(p.calculateFinalPrice());
        //ensure size
        fillString(&prodID);fillString(&prodName);fillString(&quantity);fillString(&price);
        // print row
        printRep(' ',' ',14 -1);
        cout<<"| "<<prodID<<"| "<<prodName<<"| "<<price<<"| "<<quantity<<"|\n";
        printRep(' ',' ',14); printRep('_','_',44);cout<<"\n";

    }
}

/**
    Runs the Product Management aspect of program
    @param products - Product vector
*/
void runPM(InventoryManager& manager){

    int option;
    const int center = 27;
    do {
        line();
        cout<<"\n";
        printRep(' ',' ',center);
		cout << "====== PRODUCT MENU =======" << endl;
		printRep(' ',' ',center);
		cout << "1. Add a new product to inventory" << endl;
		printRep(' ',' ',center);
		cout << "2. Remove a product" << endl;
        printRep(' ',' ',center);
		cout << "3. Display all products" << endl;
		printRep(' ',' ',center);
		cout << "4. Search for a product by ID" << endl;
		printRep(' ',' ',center);
		cout << "5. Sort products by price or quantity " << endl;
		printRep(' ',' ',center);
		cout << "0. Back\n" << endl;
		printRep(' ',' ',center);
		cout << "===========================\n" << endl;
		printRep(' ',' ',center);
		cout << "Select option: ";

		cin >> option ;


		switch(option) {

		case 1: {

            int subOption;
            cout<<"\n";
            printRep(' ',' ',center);
            cout << "========== Add product ==========" << endl;
            printRep(' ',' ',center);
            cout << "1. Add regular product" << endl;
            printRep(' ',' ',center);
            cout << "2. Add discounted product" << endl;
            printRep(' ',' ',center);
            cout << "3. Add taxable product" << endl;
            printRep(' ',' ',center);
            cout << "===========================" << endl;
            printRep(' ',' ',center);
            cout << "Select option: ";

            cin >> subOption;

			string  productName;
			double productPrice;
			int productID,productQuantity;

            printRep(' ',' ',center);
			cout << "Enter the product ID: ";
			cin >> productID;

            printRep(' ',' ',center);
			cout << "Enter the product name: ";
			cin >> productName;

            printRep(' ',' ',center);
			cout << "Enter the product price: ";
			cin >> productPrice;

            printRep(' ',' ',center);
			cout << "Enter the product quantity: ";
			cin >> productQuantity;

            if(subOption == 1) {

                manager.addNewProduct(make_shared<Product>(productName, productPrice, productID, productQuantity));

            } else if(subOption == 2) {

                double productDiscount;
                printRep(' ',' ',center);
                cout << "Enter product discount: ";
                cin >> productDiscount;

                manager.addNewProduct(make_shared<DiscountedProduct>(productName, productPrice, productID, productQuantity, productDiscount));

            }else if(subOption == 3) {

                double productTax;
                printRep(' ',' ',center);cout << "Enter product tax: ";
                cin >> productTax;

                manager.addNewProduct(make_shared<TaxableProduct>(productName, productPrice, productID, productQuantity,productTax));
            }

            cout<<"\n";
            printRep(' ',' ',center);
			cout << "Product successfully added!\n" << endl; pause(2000);
			break;
		}

		case 2:

			break;

		case 3:

            manager.displayAllProducts();
            pause(2000);
			break;


		case 4: {

			string productName;
			cout<<"\n";
			printRep(' ',' ',center);
			cout << "Enter the name of the product you are looking for: ";
			cin >> productName;

			/**
			@todo insert search code
			*/
			break;
		}

		case 0:
			break;

		default:
            cout<<"\n";
            printRep(' ',' ',center);
			cout << "Invalid option. Try again.\n";

		}

	} while(option != 0) ;
}
/**
    Runs the Order Processing aspect of the program
*/
void runOP(){
    int option;
    const int center = 27;

    do{
        line();
        cout<<"\n";
        printRep(' ',' ',center);
		cout << "======= ORDER MENU ========" << endl;
		printRep(' ',' ',center);
		cout << "1. Display all queued Orders" << endl;
		printRep(' ',' ',center);
		cout << "2. Process orders" << endl;
		printRep(' ',' ',center);
		cout << "3. Receive new orders into queue" << endl;
		printRep(' ',' ',center);
		cout << "0. Back\n" << endl;
		printRep(' ',' ',center);
		cout << "===========================\n" << endl;
		printRep(' ',' ',center);
		cout << "Select option: ";

		cin >> option ;

		switch(option){

            case 1:{break;}

            case 2:{break;}

            case 3:{break;}

            case 0:{break;}

            default: {
                cout<<"\n";
                printRep(' ',' ',center); cout << "Invalid option. Try again.\n";
            }
		}
    } while(option != 0);


}


int main()
{
    map<int, shared_ptr<Product>> productMap;
    InventoryManager manager(productMap);

    int option;


	const int reps= 65, center = 28; // char repetitions

    printChars('*',' ',reps);
    printChars('*',' ',reps);
    pause(2000);
    printChars('=',' ',reps);
    printRep(' ',' ',center);
    cout<< "Welcome to Nexus LogiQ\n";
    cout<< "\n";
    printChars('=',' ',reps);
    printChars('*',' ',reps);
    printChars('*',' ',reps);
    pause(2000);


    /* Main Menu and Options */

    do{
        line();
        cout<<"\n";
        printRep(' ',' ',center);     cout<<"-----------------------------\n";
        printRep(' ',' ',center - 1); cout<< "<| Nexus LogiQ Administration |>\n";
        printRep(' ',' ',center);     cout<<"-----------------------------\n";

        printRep(' ',' ',center); cout << "========== MENU ==========\n" << endl;
        printRep(' ',' ',center); cout <<"1. Product Management Page\n";
        printRep(' ',' ',center); cout<<"2. Order Processing Page\n";
        printRep(' ',' ',center); cout<< "3. Help\n";
        printRep(' ',' ',center); cout << "-1. Exit\n";
        printRep(' ',' ',center); cout << "===========================\n" << endl;
        printRep(' ',' ',center); cout << "Select option: ";
        cin>>option;


        switch(option){
            case 1: {
                runPM(manager);
                break;
            }
            case 2: {
                runOP();
                break;
            }
            case 3:{
                cout<<"\n";
                printRep(' ',' ',center); cout<< "Help currently unavailable. Sorry :0 :(\n";
                pause(2000);
                break;
            }
            case -1: {
                cout<<"\n";
                printRep(' ',' ',center); cout << "Exiting system...\n";
                pause(2000);
                break;
            }
            default: {
                cout<<"\n";
                printRep(' ',' ',center); cout << "Invalid option. Try again.\n";
                break;
            }
        }



        }while(option != -1);
        cout<<"\n";
        printRep(' ',' ',center); cout << "Hope you enjoyed using the system :) BYE!";
	return 0;
}

