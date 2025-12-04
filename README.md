# Restaurant-Management-System
Restaurant Order Management System (C++ Console Application)

This document describes the structure and functionality of the provided C++ program, which implements a text-based console application for managing restaurant operations, including menu maintenance, table ordering, and detailed billing.

I. System Overview and Purpose

The program serves as a management utility for restaurant staff, providing two main user roles: Admin and Customer/Waiter.

Admin Panel: Allows management staff to view, add, and remove items from the daily menu, which is stored persistently in a file (menu.txt).

Customer/Waiter Interface: Handles the daily operations, including taking new orders for tables, modifying existing orders, viewing the menu, and generating detailed bills with automatic tax and discount calculations.

II. Core Features

1. File Handling and Menu Management

The menu data is managed entirely through a plain text file (menu.txt).

Menu Storage: Each menu item's name (where spaces are replaced with underscores _), price, and available stock quantity are stored on a separate line in menu.txt.

countItems: Scans menu.txt to determine the total number of items, dynamically sizing necessary arrays.

loadMenu / viewMenu: Reads the current item list, prices, and stock into dynamic arrays in memory for use during ordering.

modifyMenu: Writes the updated stock levels back to menu.txt after orders are finalized.

2. Order Processing and Table Management

Dynamic Order Tracking: The system supports up to 20 tables (MAX_TABLES). Orders are tracked using a 2D dynamic array (int** orders), where each row represents a table, and columns track the quantity of each menu item ordered.

takeOrder: Guides the user through selecting a table (marking it as occupied), entering the number of guests, and repeatedly adding item quantities from the menu. It checks against availableStock.

modifyOrder: Allows changes to an existing order, automatically adjusting the availableStock when quantities are increased or decreased.

viewOrder: Displays the current items, quantities, and individual totals for an occupied table.

3. Advanced Billing and History

generateBill: Calculates the total cost of all ordered items for a table.

Tax Calculation (getTax): Applies a variable tax rate based on the final total bill amount (e.g., higher bills incur higher percentage taxes).

Rs. 0 - 100: 0.0%

Rs. 101 - 500: 0.1%

... up to 2.5% for bills > Rs. 10,000.

Discount Calculation (getDiscount): Applies a variable discount based on the bill amount after tax.

Rs. 100 - 1000: 2.0%

... up to 10.0% for bills > Rs. 10,000.

spliteBill: Calculates the per-person cost by dividing the final bill by the number of guests entered for the table.

orderHistory: Appends the complete order and final bill details (including tax and discount information) to an external file (order_history.txt).

III. Technical Implementation Highlights (C++ Pointers and Arrays)

The code relies heavily on custom functions to handle common tasks, demonstrating a deep understanding of memory management and C-style string manipulation:

Custom Dynamic String/Array Handling:

regrowChar: Dynamically reallocates a C-style string (char*) to add a new character (input), simulating dynamic array behavior, which is essential for reading user input of unknown length.

getLen, isEqual: Custom functions for string length and comparison (like built-in strlen and strcmp).

Custom Input Validation and Conversion:

isDigitsOnly, isDigitsandDoubleOnly, containSpace: Functions to validate raw user input read from cin.getline before conversion.

charToInt, charToDouble: Custom implementations for converting C-style string representations of numbers into int and double types, respectively.

Memory Management: The program correctly uses new[] to allocate memory for arrays of item names, prices, stock, and the 2D orders array. Crucially, the main and Customer functions include corresponding delete[] calls to prevent memory leaks.
