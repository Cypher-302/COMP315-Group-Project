#include <iostream>

#include <thread>
#include <vector>
#include <string>
#include "include/Product.h"
#include "include/DiscountedProduct.h"
#include "include/TaxableProduct.h"
#include "include/InventoryManager.h"
#include "include/Utility.h"

using namespace std;
using namespace Utility;

/**
    Runs the Product Management aspect of program
    @param products - Product vector
*/
map<int, shared_ptr<Product>> productMap;
    InventoryManager manager(productMap);

void removeProduct(){
    int center = 20;
    cout << "====== PRODUCT SEARCH ======" << endl;
    printRep(' ',' ',center);

    cout << "Enter Product ID: ";
    int productID;
    cin >> productID;

    printRep(' ',' ',center);
    cout << "============================" << endl;
    if(manager.removeProduct(productID)){
        cout << "====== PRODUCT REMOVED ======" << endl;
        printRep(' ',' ',center);

        cout << "The product has been successfully removed." << endl;

        printRep(' ',' ',center);
        cout << "=============================" << endl;
        return;
    }
        cout << "====== PRODUCT NOT FOUND ======" << endl;
        printRep(' ',' ',center);

        cout << "No product with the given ID was found." << endl;

        printRep(' ',' ',center);
        cout << "===============================" << endl;

}





void getUpdate(){
    int center = 20;
    printRep(' ',' ',center);
    cout << "========== Search / Update Product ==========" << endl;


    printRep(' ',' ',center);
    cout << "Enter productID: ";

    int productID;
    cin >> productID;

    printRep(' ',' ',center);
    cout << "Enter Quantity: ";

    int quant;
    cin >> quant;

    manager.updateProduct(productID, quant);
    printRep(' ',' ',center);

    cout << "Product Updated" << endl;
    cout << "============================================" << endl;


}

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
		cout << "6. Update Product " << endl;
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
			cout << "Product successfully added!\n" << endl; pause(1000);
			break;
		}

		case 2:
            // We still need to look at the "Remove Product" Implementation
            removeProduct();
			break;

		case 3:

            manager.displayAllProducts();
            pause(1000);
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
		case 5: {
            int subOption;
            cout<<"\n";
            printRep(' ',' ',center);
            cout << "========= Sort products =========" << endl;
            printRep(' ',' ',center);
            cout << "1. Sort by Price and Display" << endl;
            printRep(' ',' ',center);
            cout << "2. Sort by Quantity and Display" << endl;
            printRep(' ',' ',center);
            cout << "===========================" << endl;
            printRep(' ',' ',center);
            cout << "Select option: ";

            cin >> subOption;
            if(subOption==1){
                manager.sortAndDisplayProductByPrice();
            }else if(subOption==2){
                manager.sortAndDisplayProductByQuantity();
            }else{
                cout<< "Invalid option Entered";
            }
            break;
		}

		case 6: {

		   if(manager.displayAllProducts()){
                getUpdate();
                break;
		    }

                        printRep(' ', ' ', center);
            cout << "============================" << endl;

            printRep(' ', ' ', center);
            cout << "There are no Products in Inventory" << endl;

            printRep(' ', ' ', center);
            cout << "============================" << endl;

            runPM(manager);

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


    int option;


	const int reps= 65, center = 28; // char repetitions

    printChars('*',' ',reps);
    printChars('*',' ',reps);
    pause(1000);
    printChars('=',' ',reps);
    printRep(' ',' ',center);
    cout<< "Welcome to Nexus LogiQ\n";
    cout<< "\n";
    printChars('=',' ',reps);
    printChars('*',' ',reps);
    printChars('*',' ',reps);
    pause(1000);
       if(manager.loadMap() == 0){
        std::cerr<<"Failed to load Inventory"<<endl;
       }

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

        //runs the sellected option
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
                pause(1000);
                break;
            }
            case -1: {
                cout<<"\n";
                printRep(' ',' ',center); cout << "Exiting system...\n";
                manager.storeMap();
                pause(1000);
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

