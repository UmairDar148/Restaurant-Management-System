#include<iostream>
#include<fstream>
using namespace std;

char* regrowChar(char* arr, int& size, char input) {
    char* temp = new char[size + 2];
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    temp[size] = input;
    temp[size + 1] = '\0';
    size += 1;
    delete[] arr;
    arr = temp;
    temp = nullptr;
    return arr;
}

bool isDigitsOnly(char* arr) {
    if (arr[0] == '\0') {
        return false;
    }
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] < '0' || arr[i] > '9') {
            return false;
        }
    }
    return true;
}

bool containSpace(char* arr) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == ' ') {
            return true;
        }
    }
    return false;
}
int charToInt(char* arr) {
    int num = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        num = num * 10 + (arr[i] - '0');
    }
    return num;
}
double addTax(double totalBill, double taxRate) {
    return totalBill + (totalBill * taxRate);
}
double calculateDiscount(double totalBill, double discountRate) {
    return totalBill - (totalBill * discountRate);
}
void displayIntro() {
    cout << "\t\t\t =============================================== \n";
    cout << "\t\t\t| Welcome to Restaurant order Management System |\n";
    cout << "\t\t\t =============================================== \n";
}
double getTax(double& totalBill) {
    if (totalBill >= 0.0 && totalBill <= 100.0) {
        totalBill = addTax(totalBill, 0.0);
        return 0.0;
    }
    else if (totalBill > 100.0 && totalBill <= 500.0) {
        totalBill = addTax(totalBill, 0.001);
        return 0.1;
    }
    else if (totalBill > 500.0 && totalBill <= 1000.0) {
        totalBill = addTax(totalBill, 0.005);
        return 0.5;
    }
    else if (totalBill > 1000.0 && totalBill <= 10000.0) {
        totalBill = addTax(totalBill, 0.01);
        return 1.0;
    }
    else if (totalBill > 10000.0) {
        totalBill = addTax(totalBill, 0.025);
        return 2.5;
    }
    return 0.0;
}
int getLen(char* arr) {
    int len = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        len++;
    }
    return len;
}
bool isEqual(char arr1[], char arr2[]) {
    if (getLen(arr1) != getLen(arr2)) {
        return false;
    }
    for (int i = 0; i < getLen(arr1); i++) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

double getDiscount(double& totalBill) {
    if (totalBill >= 100.0 && totalBill <= 1000.0) {
        totalBill = calculateDiscount(totalBill, 0.02);
        return 2.0;
    }
    else if (totalBill > 1000.0 && totalBill <= 5000.0) {
        totalBill = calculateDiscount(totalBill, 0.05);
        return 5.0;
    }
    else if (totalBill > 5000.0 && totalBill <= 10000.0) {
        totalBill = calculateDiscount(totalBill, 0.07);
        return 7.0;
    }
    else if (totalBill > 10000.0) {
        totalBill = calculateDiscount(totalBill, 0.1);
        return 10.0;
    }
    else if (totalBill < 100.0) {
        return 0.0;
    }
    return 0.0;
}
void countItems(int& itemCount) {
    ifstream read("menu.txt");
    if (!read) {
        cout << "Error opening menu.txt file!" << endl;
        return;
    }
    char buffer[1000];
    while (read.getline(buffer, 1000)) {
        itemCount++;
    }
    read.close();
}
void generateBill(int tableNumber, int* orderRow, char** itemNames, double* itemPrices, int itemCount, double& totalBill) {
    cout << "==========================================================\n";
    cout << "================== Order Summary =========================\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Order for table " << tableNumber << ":\n";
    cout << "Item Number\tItem Name\tPrice\tQuantity\tTotal\n";
    for (int i = 0; i < itemCount; i++) {
        if (orderRow[i] > 0) {
            double itemTotal = orderRow[i] * itemPrices[i];
            totalBill += itemTotal;
            cout << (i + 1) << "\t\t" << itemNames[i] << "\t\t" << itemPrices[i] << "\t" << orderRow[i] << "\t\t" << itemTotal << endl;
        }
    }
    if (totalBill == 0.0) {
        cout << "No items ordered for table " << tableNumber << "." << endl;
        return;
    }
    double discount;
    double tax;
    tax = getTax(totalBill);
    cout << "Tax Apllied: " << tax << " %" << endl;;
    cout << "Bill: Rs. " << totalBill << endl;
    discount = getDiscount(totalBill);
    cout << "Discount Applied: " << discount << " %" << endl;
    cout << "-----------------------------------------------------------\n";
    cout << "Total Bill After Discount for table " << tableNumber << ": Rs. " << totalBill << endl;
    cout << "-----------------------------------------------------------\n";

}
void loadMenu(int itemCount, char** itemNames, double itemPrices[], int availableStock[]) {
    ifstream read("menu.txt");
    if (!read) {
        cout << "Error opening menu.txt file!" << endl;
        return;
    }
    int index = 0;
    while (index < itemCount && read >> itemNames[index] >> itemPrices[index] >> availableStock[index]) {
        index++;
    }
    read.close();
    cout << "==========================================================\n";
    cout << "================== Today's Menu ==========================\n";
    cout << "Item Number\tItem Name\tPrice\tAvailable quantity\n";
    cout << "----------------------------------------------------------\n";

    for (int i = 0; i < itemCount; i++) {
        cout << i + 1 << "\t\t";
        for (int j = 0; itemNames[i][j] != '\0'; j++) {
            if (itemNames[i][j] == '_') {
                cout << " ";
            }
            else {
                cout << itemNames[i][j];
            }
        }
        cout << "\t\t" << itemPrices[i] << "\t\t" << availableStock[i] << endl;
    }
    cout << "----------------------------------------------------------\n";
}
void modifyOrder(int itemCount, char** itemNames, int* availableStock, double* itemPrices, int** orders, int tableNumber) {
    int itemNumber, quantity;
    cout << "==========================================================\n";
    cout << "================== Modify Order ==========================\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Your current order:\n";
    for (int i = 0; i < itemCount; i++) {
        if (orders[tableNumber - 1][i] > 0) {
            cout << i + 1 << ". " << itemNames[i] << " (Quantity: " << orders[tableNumber - 1][i] << " )" << endl;
        }
    }
    cout << "\n\n";
    cout << "================== Today's Menu ==========================\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Item Number\tItem Name\tPrice\tAvailable quantity\n";
    cout << "----------------------------------------------------------\n";
    for (int i = 0; i < itemCount; i++) {
        cout << i + 1 << "\t\t";
        for (int j = 0; itemNames[i][j] != '\0'; j++) {
            if (itemNames[i][j] == '_') {
                cout << " ";
            }
            else {
                cout << itemNames[i][j];
            }
        }
        cout << "\t\t" << itemPrices[i] << "\t\t" << availableStock[i] << endl;
    }
    cout << "----------------------------------------------------------\n";
    char itemNumberArr[100];
    while (true) {
        cout << ">> Enter item number to modify or 0 to finish: ";
        cin.getline(itemNumberArr, 100);
        if (!isDigitsOnly(itemNumberArr)) {
            cout << "Invalid Input! " << endl;
            continue;
        }
        itemNumber = charToInt(itemNumberArr);
        if (itemNumber == 0) {
            cout << "Order modification completed.\n";
            break;
        }
        if (itemNumber < 1 || itemNumber > itemCount) {
            cout << "Invalid item number. Please try again!" << endl;
            continue;
        }
        itemNumber--;
        char quantityArr[100];
        while (true) {
            cout << "Enter new quanity for " << itemNames[itemNumber] << ": ";
            cin.getline(quantityArr, 100);
            if (!isDigitsOnly(quantityArr)) {
                cout << "Invalid Input! " << endl;
                continue;
            }
            quantity = charToInt(quantityArr);
            if (quantity < 0 || quantity >(orders[tableNumber - 1][itemNumber] + availableStock[itemNumber])) {
                cout << "Invalid quantity!" << endl;
                continue;
            }
            break;
        }
        availableStock[itemNumber] += orders[tableNumber - 1][itemNumber];
        orders[tableNumber - 1][itemNumber] = quantity;
        availableStock[itemNumber] -= quantity;
        if (quantity == 0) {
            cout << itemNames[itemNumber] << " removed from table " << tableNumber << ".\n";
        }
        else {
            cout << "Updated " << itemNames[itemNumber] << " to " << quantity << " for table " << tableNumber << ".\n";
        }
    }
}

void spliteBill(int tableNumber, int* orderRow, char** itemNames, double* itemPrices, int itemCount, int totalGuests) {
    if (totalGuests <= 0) {
        cout << "Invalid number of guests. Cannot split bill." << endl;
        return;
    }
    double totalBill = 0.0;
    generateBill(tableNumber, orderRow, itemNames, itemPrices, itemCount, totalBill);
    double splitAmount = totalBill / totalGuests;
    cout << "Each guest at table " << tableNumber << " should pay: Rs. " << splitAmount << endl;
}

void orderHistory(int tableNumber, int* orderRow, char** itemNames, double* itemPrices, int itemCount) {
    ofstream historyFile("order_history.txt", ios::app);
    if (!historyFile) {
        cout << "Error opening order_history.txt file!" << endl;
        return;
    }
    historyFile << "Order for table " << tableNumber << ":\n";
    historyFile << "Item Number\tItem Name\tPrice\tQuantity\tTotal\n";
    historyFile << "-----------------------------------------------------------\n";
    double totalBill = 0.0;
    for (int i = 0; i < itemCount; i++) {
        if (orderRow[i] > 0) {
            double itemTotal = orderRow[i] * itemPrices[i];
            totalBill += itemTotal;
            historyFile << i + 1 << "\t\t\t" << itemNames[i] << "\t\t" << itemPrices[i] << "\t" << orderRow[i] << "\t\t\t" << itemTotal << endl;
        }
    }
    historyFile << "Bill for table " << tableNumber << ": Rs. " << totalBill << endl;
    double tax = getTax(totalBill);
    historyFile << "Tax Applied: " << tax << "%" << endl;
    double discount = getDiscount(totalBill);
    historyFile << "Discount: " << discount << "%" << endl;
    historyFile << "Total Bill for table " << tableNumber << ": Rs. " << totalBill << endl;
    historyFile << "-----------------------------------------------------------\n";
    historyFile.close();

}
void modifyMenu(int itemCount, char** itemNames, double* itemPrices, int* availableStock) {
    ofstream write("menu.txt");
    if (!write) {
        cout << "Error opening menu.txt file while updation!" << endl;
        return;
    }
    for (int i = 0; i < itemCount; i++) {
        write << itemNames[i] << " " << itemPrices[i] << " " << availableStock[i] << endl;
    }
    write.close();

}
void takeOrder(int itemCount, char** itemNames, double* itemPrices, int* availableStock, int** orders, int MAX_TABLES, bool* tableOccupied, int* guestsQuantity) {
    cout << "\n----------------- Take Order -----------------------------\n";
    cout << endl;
    char tableNumberArr[100];
    int tableNumber, itemNumber;
    bool tableSelected = false;
    while (true) {
        if (tableSelected) {
            break;
        }
        cout << ">> Enter table number(1 to " << MAX_TABLES << " ,0 to cancel): ";
        cin.getline(tableNumberArr, 100);
        if (!isDigitsOnly(tableNumberArr)) {
            cout << "Invalid table Number. Please try again! " << endl;
            continue;
        }
        tableNumber = charToInt(tableNumberArr);
        if (tableNumber == 0) {
            cout << "Order cancelled.\n";
            return;
        }
        if (!(tableNumber >= 1 && tableNumber <= MAX_TABLES)) {
            cout << "Invalid table number. Please try again!" << endl;
            continue;
        }
        if (tableOccupied[tableNumber - 1]) {
            cout << "Table " << tableNumber << " is already occupied. Please choose another table." << endl;
            continue;
        }
        tableOccupied[tableNumber - 1] = true;
        tableSelected = true;
    }
    char totalguestArr[100];
    int totalguest;
    while (true) {
        cout << ">> Enter Number of guests at table " << tableNumber << ": ";
        cin.getline(totalguestArr, 100);
        if (!isDigitsOnly(totalguestArr)) {
            cout << "Invalid number of guests!" << endl;
            continue;
        }
        totalguest = charToInt(totalguestArr);
        if (!(totalguest > 0)) {
            cout << "Invalid number of guests. Please enter a positive number." << endl;
        }
        else {
            break;
        }
    }
    guestsQuantity[tableNumber - 1] = totalguest;
    cout << ">> Enter item numbers to order (1 to " << itemCount << ")" << endl;
    cout << ">> Enter 0 to finish ordering." << endl;
    char itemNumberArr[100];
    while (true) {
        cout << ">> Enter item number for table " << tableNumber << ": ";
        cin.getline(itemNumberArr, 100);
        if (!isDigitsOnly(itemNumberArr)) {
            cout << "Invalid Input! " << endl;
            continue;
        }
        itemNumber = charToInt(itemNumberArr);
        if (itemNumber == 0) {
            cout << "Order completed for table " << tableNumber << ".\n";
            break;
        }
        if (itemNumber < 1 || itemNumber > itemCount) {
            cout << "Invalid item number. Please try again!" << endl;
        }
        else {
            itemNumber--;
            if (availableStock[itemNumber] == 0) {
                cout << "Sorry, " << itemNames[itemNumber] << " is out of stock!" << endl;
                cout << "Please choose another item." << endl;
            }
            else {
                int quantity;
                char quantityArr[100];
                while (true) {
                    cout << ">> Enter quantity for " << itemNames[itemNumber] << ": ";
                    cin.getline(quantityArr, 100);
                    if (!isDigitsOnly(quantityArr) || containSpace(quantityArr)) {
                        cout << "Invalid Input or input may contain space!" << endl;
                        continue;
                    }
                    quantity = charToInt(quantityArr);
                    if (quantity < 0) {
                        cout << "Invalid quantity. Please enter a positive number." << endl;
                    }
                    else if (quantity > availableStock[itemNumber]) {
                        cout << "Sorry, we only have " << availableStock[itemNumber] << " of " << itemNames[itemNumber] << endl;
                        cout << "Please enter a valid quantity: " << endl;
                    }
                    else {
                        orders[tableNumber - 1][itemNumber] += quantity;
                        availableStock[itemNumber] -= quantity;
                        cout << "Added " << quantity << " of " << itemNames[itemNumber] << " to table " << tableNumber << ".\n";
                        break;
                    }
                }
            }
        }
    }
    char choice[100];
    while (true) {
        cout << ">> Do you want to modify your order? (y/n): ";
        cin.getline(choice, 100);
        if (getLen(choice) > 1) {
            cout << "Invalid Input! " << endl;
            continue;
        }
        if (choice[0] == 'y' || choice[0] == 'Y') {
            modifyOrder(itemCount, itemNames, availableStock, itemPrices, orders, tableNumber);
            break;
        }
        else if (choice[0] == 'n' || choice[0] == 'N') {
            cout << "Order for table " << tableNumber << " is finalized.\n";
            break;
        }
        else {
            cout << "Invalid choice. Order for table " << tableNumber << " is finalized.\n";
        }
    }double totalBill = 0.0;

    char billChoice[100];
    while (true) {
        cout << ">> Do you want to pay the bill for table " << tableNumber << "? (y/n): ";
        cin.getline(billChoice, 100);
        if (getLen(billChoice) > 1) {
            cout << "Invalid Input! " << endl;
            continue;
        }
        if (billChoice[0] == 'y' || billChoice[0] == 'Y') {
            cout << "\n\n";
            char split[100];
            while (true) {
                cout << "Do you want to split the bill(y/n): ";
                cin.getline(split, 100);
                if (getLen(split) > 1) {
                    cout << "Invalid Input! ";
                    continue;
                }
                if (split[0] == 'y' || split[0] == 'Y') {
                    spliteBill(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount, totalguest);
                    orderHistory(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount);
                    // Free the table and reset its orders
                    tableOccupied[tableNumber - 1] = false;
                    for (int i = 0; i < itemCount; i++) {
                        orders[tableNumber - 1][i] = 0;
                    }
                    break;
                }
                else if (split[0] == 'n' || split[0] == 'N') {
                    cout << "Generating bill for table " << tableNumber << ".\n";
                    double totalBill = 0.0;
                    generateBill(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount, totalBill);
                    orderHistory(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount);
                    // Free the table and reset its orders
                    tableOccupied[tableNumber - 1] = false;
                    for (int i = 0; i < itemCount; i++) {
                        orders[tableNumber - 1][i] = 0;
                    }
                    break;
                }
                else {
                    cout << "Invalid choice. Please try again!" << endl;
                }
            }
            break;
        }
        else if (billChoice[0] == 'N' || billChoice[0] == 'n') {
            break;
        }
        else {
            cout << "Invalid Input!" << endl;
        }
    }
}

void viewMenu(int itemCount, char** itemNames, double* itemPrices, int* availableStock, bool& firstTimeAdd, bool& AddNewLine) {
    ifstream readfile("menu.txt");
    if (!readfile) {
        cout << "Error opening menu.txt file for reading! " << endl;
        firstTimeAdd = true;
        return;
    }
    int index = 0;
    char arr[100];
    readfile >> arr;
    if (getLen(arr) == 0) {
        AddNewLine = false;
    }
    readfile.close();
    ifstream read("menu.txt");
    if (!read) {
        cout << "Error opening menu.txt file for reading! " << endl;
        return;
    }
    while (index < itemCount && read >> itemNames[index] >> itemPrices[index] >> availableStock[index]) {
        index++;
    }
    cout << "Current Stock: " << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "Item Number\tItem Name\tItem Price\tItem Quantity" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << i + 1 << "\t\t";
        for (int j = 0; itemNames[i][j] != '\0'; j++) {
            if (itemNames[i][j] == '_') {
                cout << " ";
            }
            else {
                cout << itemNames[i][j];
            }

        }
        cout << "\t\t" << itemPrices[i] << "\t\t" << availableStock[i] << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
    read.close();
}
void payBill(int itemCount, char** itemNames, double* itemPrices, int** orders, bool* tableOccupied, int* availableStock, int MAX_TABLES, int* guestQuantity) {
    char tableNumberArr[100];
    int tableNumber;
    cout << ">> Enter table number to pay bill (1 to " << MAX_TABLES << "): ";
    cin.getline(tableNumberArr, 100);
    if (!isDigitsOnly(tableNumberArr)) {
        cout << "Invalid table number! " << endl;
        return;
    }
    tableNumber = charToInt(tableNumberArr);
    if (tableNumber < 1 || tableNumber > MAX_TABLES) {
        cout << "Invalid table number.\n";
        return;
    }
    if (!tableOccupied[tableNumber - 1]) {
        cout << "Table " << tableNumber << " is not occupied. \n";
        return;
    }
    int totalguest = guestQuantity[tableNumber - 1];
    double totalBill = 0.0;
    char split[100];
    while (true) {
        cout << ">> Do you want to split the bill(y/n): ";
        cin.getline(split, 100);
        if (getLen(split) > 1) {
            cout << "Invalid Input! " << endl;
            continue;
        }
        if (split[0] == 'y' || split[0] == 'Y') {
            spliteBill(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount, totalguest);
            orderHistory(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount);
            // Free the table and reset its orders
            tableOccupied[tableNumber - 1] = false;
            for (int i = 0; i < itemCount; i++) {
                orders[tableNumber - 1][i] = 0;
            }
            break;
        }
        else if (split[0] == 'n' || split[0] == 'N') {
            cout << "Generating bill for table " << tableNumber << "....\n";
            double totalBill = 0.0;
            generateBill(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount, totalBill);
            orderHistory(tableNumber, orders[tableNumber - 1], itemNames, itemPrices, itemCount);
            // Free the table and reset its orders
            tableOccupied[tableNumber - 1] = false;
            for (int i = 0; i < itemCount; i++) {
                orders[tableNumber - 1][i] = 0;
            }
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again!" << endl;
        }
    }
}
void viewOrder(int itemCount, char** itemNames, double* itemPrices, int* orderRow, int tableNumber) {
    cout << "==========================================================\n";
    cout << "================== Current Order =========================\n";
    cout << "-----------------------------------------------------------\n";
    cout << "Order for table " << tableNumber << ":\n";
    cout << "Item Number\tItem Name\tPrice\tQuantity\tTotal\n";
    for (int i = 0; i < itemCount; i++) {
        if (orderRow[i] > 0) {
            double itemTotal = orderRow[i] * itemPrices[i];
            cout << (i + 1) << "\t\t";
            for (int j = 0; itemNames[i][j] != '\0'; j++) {
                if (itemNames[i][j] == '_') {
                    cout << " ";
                }
                else {
                    cout << itemNames[i][j];
                }
            }
            cout << "\t\t" << itemPrices[i] << "\t" << orderRow[i] << "\t\t" << itemTotal << endl;
        }
    }
}
void Customer() {
    cout << "\n\n";
    int itemCount = 0;
    int MAX_TABLES = 20;
    bool* tableOccupied = new bool[MAX_TABLES] {};
    countItems(itemCount);
    int** orders = new int* [MAX_TABLES];
    for (int i = 0; i < MAX_TABLES; i++) {
        orders[i] = new int[itemCount] {};
    }
    char** itemNames = new char* [itemCount];
    for (int i = 0; i < itemCount; i++) {
        itemNames[i] = new char[100]; //let's assume maximum length of each item is 100 characters
    }
    double* itemPrices = new double[itemCount];
    int* availableStock = new int[itemCount];
    int* guestsQuantity = new int[MAX_TABLES] {};
    char choice[100];
    loadMenu(itemCount, itemNames, itemPrices, availableStock);
    while (true) {

        cout << "\n ------------- New Table Order or Action --------------- \n";
        cout << "| 1. Take Order                                         |\n";
        cout << "| 2. Get Bill                                           |\n";
        cout << "| 3. View Current Order                                 |\n";
        cout << "| 4. View Menu                                          |" << endl;
        cout << "| 0. Exit                                               |\n";
        cout << " ------------------------------------------------------- \n";
        cout << ">> Enter your choice: ";
        cin.getline(choice, 100);
        if (getLen(choice) > 1) {
            cout << "Invalid Input: ";
            continue;
        }
        if (choice[0] == '0') {
            cout << " ============================= \n";
            cout << "| Exiting...........          |" << endl;
            cout << " ============================= \n";
            break;
        }
        else if (choice[0] == '1') {
            takeOrder(itemCount, itemNames, itemPrices, availableStock, orders, MAX_TABLES, tableOccupied, guestsQuantity);
            modifyMenu(itemCount, itemNames, itemPrices, availableStock);
        }
        else if (choice[0] == '2') {
            payBill(itemCount, itemNames, itemPrices, orders, tableOccupied, availableStock, MAX_TABLES, guestsQuantity);
            modifyMenu(itemCount, itemNames, itemPrices, availableStock);
        }
        else if (choice[0] == '3') {
            char tableNumberArr[100];
            int tableNumber;
            cout << "Enter table number to view current order (1 to " << MAX_TABLES << "): ";
            cin.getline(tableNumberArr, 100);
            if (!isDigitsOnly(tableNumberArr)) {
                cout << "Invalid Input! " << endl;
                continue;
            }
            tableNumber = charToInt(tableNumberArr);
            if (tableNumber < 1 || tableNumber > MAX_TABLES) {
                cout << "Invalid table number.\n";
                continue;
            }
            if (!tableOccupied[tableNumber - 1]) {
                cout << "Table " << tableNumber << " is not occupied. \n";
                continue;
            }
            viewOrder(itemCount, itemNames, itemPrices, orders[tableNumber - 1], tableNumber);
        }
        else if (choice[0] == '4') {
            int updatedItemCount = 0;
            countItems(updatedItemCount);
            char** updatedItemNames = new char* [updatedItemCount];
            for (int i = 0; i < updatedItemCount; i++) {
                updatedItemNames[i] = new char[100];
            }
            double* updatedItemPrices = new double[updatedItemCount];
            int* updatedAvailableStock = new int[updatedItemCount];

            bool unflag = true, unseflag1 = true;
            viewMenu(updatedItemCount, updatedItemNames, updatedItemPrices, updatedAvailableStock, unflag, unseflag1);

            for (int i = 0; i < updatedItemCount; i++) {
                delete[] updatedItemNames[i];
            }
            delete[] updatedItemNames;
            delete[] updatedItemPrices;
            delete[] updatedAvailableStock;
        }

        else {
            cout << "Invalid choice. Please try again!" << endl;
        }
    }
    delete[] itemPrices;
    delete[] availableStock;
    for (int i = 0; i < itemCount; i++) {
        delete[] itemNames[i];
    }
    delete[] itemNames;
    for (int i = 0; i < MAX_TABLES; i++) {
        delete[] orders[i];
    }
    delete[] orders;
    delete[] tableOccupied;
    delete[] guestsQuantity;
}

void RWithUds(char* arr) {
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == ' ') {
            arr[i] = '_';
        }
    }
}
bool isdigits(char ch) {
    return ch >= '0' && ch <= '9';
}
bool validPriceChar(char ch) {
    return isdigits(ch) || ch == '.';
}

bool isDigitsandDoubleOnly(char* arr) {
    int len = getLen(arr);
    if (len == 0) {
        return false;
    }
    int dotCount = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        if (arr[i] == '.') {
            if (i == 0 || i == len - 1) {
                return false;
            }
            dotCount++;
            if (dotCount > 1) {
                return false;
            }
        }
        else if (!validPriceChar(arr[i])) {
            return false;
        }
    }
    return true;
}
double charToDouble(char* arr) {
    int i = 0;
    double result = 0.0;

    while (arr[i] != '\0' && arr[i] != '.') {
        result = result * 10 + (arr[i] - '0');
        i++;
    }
    if (arr[i] == '.') {
        i++;
        double frac = 0.0;
        double div = 1.0;
        while (arr[i] != '\0') {
            frac = frac * 10 + (arr[i] - '0');
            div *= 10;
            i++;
        }
        result = result + (frac / div);
    }
    return result;
}
void AddItems() {
    cout << "\t\t----------------- Add Item(s) Screen -------------------------" << endl;
    bool firstTimeAdd = false;
    int itemCount = 0;
    countItems(itemCount);
    char** itemNames = new char* [itemCount];
    for (int i = 0; i < itemCount; i++) {
        itemNames[i] = new char[100];
    }
    double* itemPrices = new double[itemCount];
    int* availableStock = new int[itemCount];
    bool addNewLine = true;
    viewMenu(itemCount, itemNames, itemPrices, availableStock, firstTimeAdd, addNewLine);
    char* itemName = nullptr;
    int NameSize = 0;
    char priceArr[100];
    double price;
    char stockArr[100];
    int stock;


    while (true) {
        bool isItemDuplicate = false;
        cout << "\n>> Enter Item Name to add: ";
        delete[] itemName;
        itemName = new char[1] {'\0'};
        NameSize = 0;
        while (true) {
            char ch;
            cin.get(ch);
            if (ch == '\n') {
                break;
            }
            itemName = regrowChar(itemName, NameSize, ch);
       }
        char itemNameduplicate[100];
       float garbage;
        ifstream read("menu.txt");
        if (!read) {
            cout << "Internal server Error! " << endl;
        } 
        RWithUds(itemName);
        while (read >> itemNameduplicate >> garbage >> garbage) {
           
            if (isEqual(itemNameduplicate, itemName)) {
                cout << "Item Already exist!";
                read.close();
                isItemDuplicate = true;
                break;
            }
        }
        if (!isItemDuplicate) {
            read.close();
            break;
        }
    }
    ofstream write("menu.txt", ios::app);
 if (!write) {
     cout << "Error opening menu.txt file for writing! " << endl;
     return;
 }
    if (!firstTimeAdd && addNewLine) {
        write << endl;
    }
    write << itemName << " ";
    while (true) {
        cout << ">> Enter price: ";
        cin.getline(priceArr, 100);
        if (!isDigitsandDoubleOnly(priceArr)) {
            cout << "Seems like invalid price! " << endl;
            continue;
        }
        price = charToDouble(priceArr);
        if (price < 0) {
            cout << "Seems like invalid price! " << endl;
            continue;
        }
        write << price << " ";
        break;
    }
    while (true) {
        cout << ">> Enter quantity: ";
        cin.getline(stockArr, 100);
        if (!isDigitsOnly(stockArr)) {
            cout << "Seems like invalid quantity! " << endl;
            continue;
        }
        stock = charToInt(stockArr);
        if (stock < 0) {
            cout << "Seems like invalid quantity! " << endl;
            continue;
        }
        write << stock;
        break;
    }
    for (int i = 0; i < NameSize; i++) {
        if (itemName[i] == '_') {
            cout << " ";
        }
        else {
            cout << itemName[i];
        }
    }
    cout << " Added succesfully! " << endl;
    write.close();
    delete[] itemName;
    delete[] itemNames;
    delete[] itemPrices;
    delete[] availableStock;
}

void removeItem() {
    cout << "\t\t----------------- Remove Item(s) Screen -------------------------" << endl;
    int itemCount = 0;
    countItems(itemCount);
    char** itemNames = new char* [itemCount];
    for (int i = 0; i < itemCount; i++) {
        itemNames[i] = new char[100];
    }
    double* itemPrices = new double[itemCount];
    int* availableStock = new int[itemCount];
    char itemNumberArr[100];
    int itemNumber;
    bool unuseflag = true, unuseflag1 = true;
    viewMenu(itemCount, itemNames, itemPrices, availableStock, unuseflag, unuseflag1);
   
    int index = 0;
    while (true) {
        cout << ">> Enter item Number to remove: ";
        cin.getline(itemNumberArr, 100);
        if (!isDigitsOnly(itemNumberArr)) {
            cout << "Invalid item Number! " << endl;
            return;
        }
        itemNumber = charToInt(itemNumberArr);
        if (itemNumber < 1 || itemNumber > itemCount) {
            cout << "Invalid item Number! " << endl;
            return;
        }
        break;
    }
    ofstream write("menu.txt");
    if (!write) {
        cout << "Error opening menu.txt file for reading! " << endl;
        return;
    }
    bool firstLine = true;
    for (int i = 0; i < itemCount; i++) {
        if (i == itemNumber - 1) {
            continue;
        }
        if (!firstLine) {
            write << endl;
        }

        write << itemNames[i] << " " << itemPrices[i] << " " << availableStock[i];
        firstLine = false;
    }

    cout << itemNames[itemNumber - 1] << " Removed successfully! " << endl;
    delete[] itemPrices;
    delete[] availableStock;
    for (int i = 0; i < itemCount; i++) {
        delete[] itemNames[i];
    }
    delete[] itemNames;
    write.close();

}
void adminStuff() {
    char choiceArr[100];
    int choice;
    cout << "\t\t =================================================================" << endl;
    cout << "\t\t|               Welcome to admin controls                         |" << endl;
    cout << "\t\t =================================================================" << endl;
    while (true) {
        cout << " -------------------------------------------" << endl;
        cout << "| 1. Add items                              |" << endl;
        cout << "| 2. Remove Items                           |" << endl;
        cout << "| 3. View Current menu                      |" << endl;
        cout << "| 0. exit                                   |" << endl;
        cout << " -------------------------------------------" << endl;
        cout << ">> Enter Your Choice: ";
        cin.getline(choiceArr, 100);
        if (!isDigitsOnly(choiceArr)) {
            cout << "Invalid choice! " << endl;
            continue;
        }
        choice = charToInt(choiceArr);
        if (choice == 0) {
            cout << " --------------------------------------" << endl;
            cout << "| Exiting...........                    |" << endl;
            cout << " --------------------------------------" << endl;
            return;
        }
        if (choice == 1) {
            AddItems();
        }
        else if (choice == 2) {
            removeItem();
        }
        else if (choice == 3) {
            int itemCount = 0;
            countItems(itemCount);
            char** itemNames = new char* [itemCount];
            for (int i = 0; i < itemCount; i++) {
                itemNames[i] = new char[100];
            }
            double* itemPrices = new double[itemCount];
            int* availableStock = new int[itemCount];
            bool  nonuseflag = true, unuseflag = true;
            viewMenu(itemCount, itemNames, itemPrices, availableStock, nonuseflag, unuseflag);
            for (int i = 0; i < itemCount; i++) {
                delete[] itemNames[i];
            }
            delete[] itemNames;
            delete[] itemPrices;
            delete[] availableStock;

        }
        else {
            cout << "Invalid input! " << endl;
        }
    }
}
void admin() {
    char adminuserName[] = "admin";
    char adminPass[] = "admin1";
    char ch;
    cout << "\t\t\t =============================================== \n";
    cout << "\t\t\t|              Welcome to Admin Panel           |\n";
    cout << "\t\t\t =============================================== \n";

    int count = 0;
    while (true) {
        char* username = nullptr;
        char* password = nullptr;
        int UserNameSize = 0, passSize = 0;
        if (count == 3) {
            cout << "Sorry, you have tried your three attempts! Please try again after a moment! " << endl;
            cout << endl;
            cout << " ============================= \n";
            cout << "| Exiting...........          |" << endl;
            cout << " ============================= \n";
            return;
        }
        cout << "\n\n\t\t------------------ Plese validate credentials --------------------" << endl;
        cout << ">> Enter username: ";
        while (true) {
            cin.get(ch);
            if (ch == '\n') {
                break;
            }
            username = regrowChar(username, UserNameSize, ch);
        }
        cout << ">> Enter Password: ";
        while (true) {
            cin.get(ch);
            if (ch == '\n') {
                break;
            }
            password = regrowChar(password, passSize, ch);
        }
        if (isEqual(username, adminuserName) && isEqual(password, adminPass)) {

            cout << "\t\t\t =============================================== \n";
            cout << "\t\t\t|              Login Successful                 |\n";
            cout << "\t\t\t =============================================== \n";

            adminStuff();
            break;
        }
        else {
            cout << "Invalid username or password! " << endl;
            count++;
        }
    }
}
int main() {
    displayIntro();
    char adminChoiceArr[100];
    int adminChoice;
    while (true) {
        cout << " --------------------------------------- " << endl;
        cout << "| Press 1 to continue as Admin          |" << endl;
        cout << "| Press 2 to continue as customer       |" << endl;
        cout << "| Press 0 to exit                       |" << endl;
        cout << " --------------------------------------- " << endl;
        cout << ">> Enter your Choice: ";
        cin.getline(adminChoiceArr, 100);
        if (!isDigitsOnly(adminChoiceArr)) {
            cout << "Invalid Choice. Please Try Again! " << endl;
            continue;
        }
        adminChoice = charToInt(adminChoiceArr);
        if (adminChoice == 1) {
            admin();
        }
        else if (adminChoice == 2) {
            Customer();
        }
        else if (adminChoice == 0) {
            cout << " ============================= \n";
            cout << "| Exiting...........          |" << endl;
            cout << " ============================= \n";
            break;
        }
        else {
            cout << "Invalid Input! " << endl;
        }
    }

    cout << "\n\n";
    cout << "\t\t\t ========================================================= \n";
    cout << "\t\t\t| Thank you for using Restaurant Order Management System! |\n";
    cout << "\t\t\t|                   Have a great day!                     |\n";
    cout << "\t\t\t ========================================================= \n\n";
    cout << " ===================================================================== \n";
    cout << "|                Developed by:                                        |\n";
    cout << "|                Muhammad Imran Butt   [L1F24BSCS0546]                |\n";
    cout << "|                Muhammad Salman Amjad [L1F24BSCS0553]                |\n";
    cout << "|                Muhammad Umair Dar    [L1F24BSCS0676]                |\n";
    cout << " ===================================================================== \n";
    cout << "\n\n";
    return 0;
}