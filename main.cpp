
#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "Library.h"
#include "Library/File/Filesystem.h"



void clearConsole() {
#ifdef _WIN32
    std::system("cls");   // Windows
#else
    std::system("clear"); // macOS / Linux
#endif
}

void pauseConsole() {
#ifdef _WIN32
    system("pause");     // Windows
#else
    system("read -n 1 -s -r -p \"Press any key to continue\""); 
#endif
}



void showMenu() {
    std::cout << R"(
=======================================================
|             UNIVERSITY LIBRARY SYSTEM              |
=======================================================
 [1] Manage Items
     ├── Add Item
     ├── Remove Item
     └── Edit Item
 [2] Manage Users
     ├── Add User
     ├── Remove User
     └── Edit User
 [3] Handle Loans
     ├── Loan Item
     └── Return Item
 [4] Search & Browse
     ├── Search by Criteria
     └── List All Records
 [0] Exit and Save
-------------------------------------------------------
 Choose an option (0–4) and press ENTER:
=======================================================
)";
}


int main() {
    // Declare the vectors to store data
    std::vector<Item*> catalog;
    std::vector<User*> users;
    std::vector<Loan*> loans;

    // Cargar datos 
    Filesystem::loadItems("Library/File/items.csv", catalog);
    Filesystem::loadUsers("Library/File/user.csv", users);
    Filesystem::loadLoans("Library/File/loan.csv", loans, users, catalog);

    Library library(catalog, users, loans); // objeto principal con los datos cargados

    bool exitProgram = false;
    int option;

    while (!exitProgram) {
     clearConsole(); 
        showMenu();

        std::cin >> option;


        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue; 
        }


        switch (option) {
            case 1:    
             library.ItemMenu();
                break;
            case 2:
            library.userMenu();
                break;
            case 3:
            library.userMenu();
                break;
            case 4:
               library.searchMenu();
                break;
            case 0:
               library.saveAll();
                std::cout << "Saving data...\n";
                exitProgram = true;
                library.cleanAll();
                break;
            default:
                std::cout << "Not valid option.\n";
               pauseConsole();
        }
    }

    return 0;
}


