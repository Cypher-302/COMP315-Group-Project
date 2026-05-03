#include "include/Product.h"
#include "include/DiscountedProduct.h"
#include "include/TaxableProduct.h"
#include "include/InventoryManager.h"
#include "include/Utility.h"
#include "include/OrderProcessor.h"

#include <iostream>
#include <thread>
#include <vector>
#include <string>

using namespace std;
using namespace Utility;

void removeProduct(std::shared_ptr<InventoryManager> manager){
    const int CENTER = 27;
    printRep(' ',' ',CENTER);
    cout << "====== PRODUCT SEARCH ======" << endl;
    printRep(' ',' ',CENTER);

    cout << "Enter Product ID: ";
    int productID;
    cin >> productID;

    printRep(' ',' ',CENTER);
    cout << "============================" << endl;
    if(manager->removeProduct(productID)){
        printRep(' ',' ',CENTER);
        cout << "====== PRODUCT REMOVED ======" << endl;
        printRep(' ',' ',CENTER);

        cout << "The product has been successfully removed." << endl;

        printRep(' ',' ',CENTER);
        cout << "=============================" << endl;
        return;
    }
        printRep(' ',' ',CENTER);
        cout << "====== PRODUCT NOT FOUND ======" << endl;
        printRep(' ',' ',CENTER);

        cout << "No product with the given ID was found." << endl;

        printRep(' ',' ',CENTER);
        cout << "===============================" << endl;

}

void showhelpPage(){
    const int CENTER = 27;
    printRep(' ',' ',CENTER);     cout <<"-----------------------------\n";
    printRep(' ',' ',CENTER - 1); cout << "<| Nexus LogiQ Help Center |>\n";
    printRep(' ',' ',CENTER);     cout <<"-----------------------------\n";

    printRep(' ',' ',CENTER); cout << "========== HELP ==========\n" << endl;

    printRep(' ',' ',CENTER); cout << "1. Product Management\n";
    printRep(' ',' ',CENTER); cout << "   - Add, update, or remove products\n";
    printRep(' ',' ',CENTER); cout << "   - View inventory details\n\n";

    printRep(' ',' ',CENTER); cout << "2. Order Processing\n";
    printRep(' ',' ',CENTER); cout << "   - Create and manage orders\n";
    printRep(' ',' ',CENTER); cout << "   - Track order status\n\n";

    printRep(' ',' ',CENTER); cout << "3. Navigation\n";
    printRep(' ',' ',CENTER); cout << "   - Use menu numbers to select options\n";
    printRep(' ',' ',CENTER); cout << "   - Enter -1 to exit the system\n\n";

    printRep(' ',' ',CENTER); cout << "4. Need More Help?\n";
    printRep(' ',' ',CENTER); cout << "   - Contact system admin\n";
    printRep(' ',' ',CENTER); cout << "   - Check documentation folder\n";

    printRep(' ',' ',CENTER); cout << "===========================\n\n";

    printRep(' ',' ',CENTER); cout << "Press any key to return to menu...";

    cin.ignore();
    cin.get();
}

void getUpdate(std::shared_ptr<InventoryManager> manager){
    const int CENTER = 27;
    printRep(' ',' ',CENTER);
    cout << "==============  Update Product =============" << endl;


    printRep(' ',' ',CENTER);
    cout << "Enter productID: ";

    int productID;
    cin >> productID;
    if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! ID must be Numerical\n";
                cin.clear();
                cin.ignore(1000, '\n');
                return;
    }

    printRep(' ',' ',CENTER);
    cout << "Enter Quantity: ";

    int quant;
    cin >> quant;
    if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! Quantity must be Numerical\n";
                cin.clear();
                cin.ignore(1000, '\n');
                return;
    }

    manager->updateProduct(productID, quant);
    printRep(' ',' ',CENTER);
    cout << "Product Updated" << endl;
    printRep(' ',' ',CENTER);

    cout << "============================================" << endl;
}

void runPM(std::shared_ptr<InventoryManager> manager){
    int option;
    const int CENTER = 27;
    do {
        line();
        cout<<"\n";
        printRep(' ',' ',CENTER);
		cout << "====== PRODUCT MENU =======" << endl;
		printRep(' ',' ',CENTER);
		cout << "1. Add a new product to inventory" << endl;
		printRep(' ',' ',CENTER);
		cout << "2. Remove a product" << endl;
        printRep(' ',' ',CENTER);
		cout << "3. Display all products" << endl;
		printRep(' ',' ',CENTER);
		cout << "4. Search for a product by ID" << endl;
		printRep(' ',' ',CENTER);
		cout << "5. Sort products by price or quantity " << endl;
		printRep(' ',' ',CENTER);
		cout << "6. Update Product " << endl;
		printRep(' ',' ',CENTER);
		cout << "0. Back\n" << endl;
		printRep(' ',' ',CENTER);
		cout << "===========================\n" << endl;
		printRep(' ',' ',CENTER);
		cout << "Select option: ";

		cin >> option ;
        if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                break;
        }

		switch(option) {

		case 1: {

            int subOption;
            cout<<"\n";
            printRep(' ',' ',CENTER);
            cout << "========== Add product ==========" << endl;
            printRep(' ',' ',CENTER);
            cout << "1. Add regular product" << endl;
            printRep(' ',' ',CENTER);
            cout << "2. Add discounted product" << endl;
            printRep(' ',' ',CENTER);
            cout << "3. Add taxable product" << endl;
            printRep(' ',' ',CENTER);
            cout << "===========================" << endl;
            printRep(' ',' ',CENTER);
            cout << "Select option: ";

            cin >> subOption;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

			string  productName;
			double productPrice;
			int productID,productQuantity;


            printRep(' ',' ',CENTER);
			cout << "Enter the product ID: ";
			cin >> productID;
            if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! ID must be Numerical\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            printRep(' ',' ',CENTER);
			cout << "Enter the product name: ";
			cin >> productName;
            if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! Name must use only allowed characters\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }
            printRep(' ',' ',CENTER);
			cout << "Enter the product price: ";
			cin >> productPrice;
            if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! Price must be Numerical\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }


            printRep(' ',' ',CENTER);
			cout << "Enter the product quantity: ";
			cin >> productQuantity;
			if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! Quantity must be Numerical\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

           if(subOption == 1) {

                manager->addNewProduct(make_shared<Product>(productName, productPrice, productID, productQuantity));

            } else if(subOption == 2) {

                double productDiscount;
                printRep(' ',' ',CENTER);
                cout << "Enter product discount: ";
                cin >> productDiscount;
                if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! Discount must be Numerical\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
                }

                manager->addNewProduct(make_shared<DiscountedProduct>(productName, productPrice, productID, productQuantity, productDiscount));

            }else if(subOption == 3) {

                double productTax;
                printRep(' ',' ',CENTER);cout << "Enter product tax: ";
                cin >> productTax;
                if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << " Invalid input! Tax must be Numerical\n";
                cin.clear();
                cin.ignore(1000, '\n');
                break;
                }

                manager->addNewProduct(make_shared<TaxableProduct>(productName, productPrice, productID, productQuantity,productTax));


            cout<<"\n";
            printRep(' ',' ',CENTER);
			cout << "Product successfully added!\n" << endl; pause(1000);
			}
			break;
		}

		case 2:

            int productID;
            cout<<"\n";
			printRep(' ',' ',CENTER);
            cout << "Enter ID of the product you want to remove: ";
            cin >> productID;
            if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << "Operation failed" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            if(manager->removeProduct(productID)) {
                printRep(' ',' ',CENTER);
                cout << "Product successfully removed!" << endl;
            } else {
                printRep(' ',' ',CENTER);
                cout << "Operation failed" << endl;
            }

			break;

		case 3:

            manager->displayAllProducts();
            pause(1000);
			break;


		case 4: {

			int productID;
			cout<<"\n";
			printRep(' ',' ',CENTER);
			cout << "Enter the ID of the product you are looking for: ";
			cin >> productID;
            if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << "Operation failed" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            cout<<"\n";
			printRep(' ',' ',CENTER);
			manager->searchProductById(productID)->display();
			break;
		}
		case 5: {
            int subOption;
            cout<<"\n";
            printRep(' ',' ',CENTER);
            cout << "========= Sort products =========" << endl;
            printRep(' ',' ',CENTER);
            cout << "1. Sort by Price and Display" << endl;
            printRep(' ',' ',CENTER);
            cout << "2. Sort by Quantity and Display" << endl;
            printRep(' ',' ',CENTER);
            cout << "===========================" << endl;
            printRep(' ',' ',CENTER);
            cout << "Select option: ";

            cin >> subOption;
            if (cin.fail()) {
                printRep(' ',' ',CENTER);
                cout << "Operation failed" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                break;
            }

            if(subOption==1){
                manager->sortAndDisplayProductByPrice();
            }else if(subOption==2){
                manager->sortAndDisplayProductByQuantity();
            }else{
                cout<< "Invalid option Entered";
            }
            break;
		}

		case 6: {

		   if(manager->displayAllProducts()){
                getUpdate(manager);
                break;
		    }

            printRep(' ', ' ', CENTER);
            cout << "============================" << endl;

            printRep(' ', ' ', CENTER);
            cout << "There are no Products in Inventory" << endl;

            printRep(' ', ' ', CENTER);
            cout << "============================" << endl;

            runPM(manager);

		    break;
		}

		case 0:
			break;

		default:
            cout<<"\n";
            printRep(' ',' ',CENTER);
			cout << "Invalid option. Try again.\n";

		}

	} while(option != 0) ;
}
/**
    Runs the Order Processing aspect of the program
*/
void runOP(OrderProcessor& orderProcessor){
    int option;
    const int CENTER = 27;

    do
    {
        line();
        cout<<"\n";
        printRep(' ',' ',CENTER);
		cout << "======= ORDER MENU ========" << endl;
		printRep(' ',' ',CENTER);
		cout << "1. Display all queued orders" << endl;
		printRep(' ',' ',CENTER);
		cout << "2. Add new order into queue" << endl;
		printRep(' ',' ',CENTER);
		cout << "3. Process orders" << endl;
		printRep(' ',' ',CENTER);
		cout << "4. Simulate random orders" << endl;
		printRep(' ',' ',CENTER);
        cout << "5. View order history" << endl;
		printRep(' ',' ',CENTER);
		cout << "0. Back\n" << endl;
		printRep(' ',' ',CENTER);
		cout << "===========================\n" << endl;
		printRep(' ',' ',CENTER);
		cout << "Select option: ";

		cin >> option ;

		switch(option)
		{
		    case 1: // display all queued orders
            {
                orderProcessor.displayQueue();
                pause(1000);
                break;
            }

            case 2: // add new order into queue
            {
                printRep(' ',' ',CENTER);
                cout << "====== NEW ORDER ENTRY ======" << endl;

                int prodID, quantity;
                static int nextOrderID = 1000; // Start manual order IDs from 1000

                printRep(' ', ' ', CENTER);
                cout << "Enter Product ID: ";
                cin >> prodID;

                printRep(' ', ' ', CENTER);
                cout << "Enter Quantity: ";
                cin >> quantity;

                // Create new order (status = false means pending/not yet processed)
                auto newOrder = make_shared<Order>(nextOrderID++, prodID, quantity, false);

                // Add to queue
                orderProcessor.addOrder(newOrder);
                printRep(' ',' ',CENTER);
                cout << "Order queued! Use 'Process orders' to fulfill it." << endl;
                pause(1000);
                break;
            }


            case 3: // process orders
            {
                orderProcessor.processQueue();
                pause(1000);
                break;
            }

            case 4: // simulate random orders
            {
                orderProcessor.runSimulation();
                pause(1000);
                break;
            }

            case 5: // view order history
            {
                orderProcessor.displayHistory();
                pause(1000);
                break;
            }

            case 0:
            {
                break;
            }

            default:
            {
                cout<<"\n";
                printRep(' ',' ',CENTER); cout << "Invalid option. Try again.\n";
            }
		}
    } while(option != 0);
}


int main()
{
    // resizes the window to 136 cols and 30 rows to fit our console output
    setupTerminal();

    int option;
    const int REPS = 65, CENTER = 28; // UI layout constants

    // welcome sequence
    printChars('*',' ',REPS);
    printChars('*',' ',REPS);
    pause(1000);
    printChars('=',' ',REPS);
    printRep(' ',' ',CENTER);
    cout << "Welcome to Nexus LogiQ\n";
    cout << "\n";
    printChars('=',' ',REPS);
    printChars('*',' ',REPS);
    printChars('*',' ',REPS);
    pause(1000);

    // Create important objects
    map<int, shared_ptr<Product>> productMap;
    auto manager = std::make_shared<InventoryManager>(productMap);
    OrderProcessor orderProcessor(manager);
    // Finished creating important objects

    // attempt to load exisiting data from persistence file
    if (manager->loadMap() != 0)
    {
        std::cerr << "Failed to load Inventory. Starting with empty map." << endl;
    }

    /* Main Menu and Options */
    do{
        line();
        cout<<"\n";
        printRep(' ',' ',CENTER);     cout <<"-----------------------------\n";
        printRep(' ',' ',CENTER - 1); cout << "<| Nexus LogiQ Administration |>\n";
        printRep(' ',' ',CENTER);     cout <<"-----------------------------\n";

        printRep(' ',' ',CENTER); cout << "========== MENU ==========\n" << endl;
        printRep(' ',' ',CENTER); cout << "1. Product Management Page\n";
        printRep(' ',' ',CENTER); cout << "2. Order Processing Page\n";
        printRep(' ',' ',CENTER); cout << "3. Help\n";
        printRep(' ',' ',CENTER); cout << "-1. Exit\n";
        printRep(' ',' ',CENTER); cout << "===========================\n" << endl;
        printRep(' ',' ',CENTER); cout << "Select option: ";

        // input validation
        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        //runs the selected option
        switch(option){
            case 1: {
                runPM(manager);
                break;
            }
            case 2: {
                runOP(orderProcessor);
                break;
            }
            case 3:{
                cout<<"\n";
                //printRep(' ',' ',CENTER); cout<< "Help currently unavailable. Sorry :0 :(\n";
                showhelpPage();
                pause(1000);
                break;
            }
            case -1: {
                cout<<"\n";
                printRep(' ',' ',CENTER); cout << "Exiting system...\n";
                manager->storeMap(); // save the current state of the inventory before closing
                pause(1000);
                break;
            }

            default: {
                cout<<"\n";
                printRep(' ',' ',CENTER); cout << "Invalid option. Try again.\n";
                break;
            }
        }
    } while(option != -1);
    cout<<"\n";
    printRep(' ',' ',CENTER); cout << "Hope you enjoyed using the system :) BYE!";
	return 0;
}
