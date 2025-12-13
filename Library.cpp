#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include<sstream>
#include<iomanip>
#include<ctime>
#include "Library.h"
#include "User/User.h"   
#include "Item/Item.h"  
#include "Loan/Loan.h"
#include "Item/E-book.h"
#include "Item/Book.h"
#include "Item/Journal.h"

void clearConsole() {
#ifdef _WIN32
    std::system("cls");   // Windows
#else
    std::system("clear"); // macOS 
#endif
}

void pauseConsole() {
#ifdef _WIN32
    system("pause");     // Windows
#else
    system("read -n 1 -s -r -p \"Press any key to continue\""); 
#endif
}




Library::Library(std::vector<Item*> _catalog, std::vector<User*> _users, std::vector<Loan*> _loans){
    catalog = _catalog;
    users = _users;
    loans = _loans;
};
   



void Library::searchAuthor(){ 
std::string selectAuthor;
std::vector<Item*>filter;
 

std::cout << " write the author that you want to search :";
std::cin.ignore();
std::getline(std::cin, selectAuthor);
for (const auto& authorTosearch : catalog) {
    if (authorTosearch->getAuthor()== selectAuthor){
        filter.push_back(authorTosearch);
    }

}
   
std::cout << "  ════════════════════════════════════════\n";
std::cout<< "  SEARCH BY AUTHOR :" << selectAuthor<<std::endl;
std::cout << "  ════════════════════════════════════════\n";

for (const auto& authorTosearch : filter){
std::cout<< "  "<<authorTosearch->getAuthor()<<std::endl;
}
  pauseConsole();
  filter.clear();

} 

void Library::searchTitle(){

std::string selectTitle;
std::vector<Item*>filter;
 

std::cout << " write the title that you want to search :";
std::cin.ignore();
std::getline(std::cin, selectTitle);
for (const auto& titleTosearch : catalog) {
    if (titleTosearch->getTitle()== selectTitle){
        filter.push_back(titleTosearch);
    }
};
   
std::cout << "  ════════════════════════════════════════\n";
std::cout<< "  SEARCH BY TITLE :" << selectTitle<<std::endl;
std::cout << "  ════════════════════════════════════════\n";

for (const auto& titleTosearch : filter){
std::cout<< "  "<<titleTosearch->getTitle()<<std::endl;
    }
pauseConsole();
filter.clear();

};

void Library::searchCategory(){

std::string selectCategory;
std::vector<Item*>filter;
 
clearConsole();
std::cout << " write the category that you want to search :";
std::cin.ignore();
std::getline(std::cin, selectCategory);
for (const auto& categoryTosearch : catalog) {
    if (categoryTosearch->getCategory()== selectCategory){
        filter.push_back(categoryTosearch);
    }
};
   
std::cout << "  ════════════════════════════════════════\n";
std::cout<< "  SEARCH BY CATEGORY :" << selectCategory<<std::endl;
std::cout << "  ════════════════════════════════════════\n";

for (const auto& categoryTosearch : filter){
std::cout<< "  "<<categoryTosearch->getCategory()<<std::endl;
};

pauseConsole();
filter.clear();
clearConsole();
} //tittle
//funcion auxiliar
Item*  Library::searchItem(std::string itemTitle){
     
    bool foundItem = false;  
    for(Item* item : catalog){
     if (item->getTitle() == itemTitle){
        return item;       
     } 
    } 
    return nullptr;
  };
 //funcion auxiliar
User*  Library::searchUser(std::string inputUser){
     
    bool foundUsar = false;  
    for(User * u : users){
     if (u->getName() == inputUser){
        return u;       
     } 
    } 
    return nullptr;
  };
 
 void Library::doLoan() {
  
    clearConsole(); 
 
    std::string inputName;
    std::cout << " Username: ";
    std::cin.ignore();
    std::getline(std::cin, inputName);

    User* foundUser = searchUser(inputName);

    if (foundUser == nullptr) {
        std::cout << " User not found in the system." << std::endl;
        return;
    }
            if (foundUser->canBorrow()) {
                
                std::cout << "\n User can borrow books.\n";
                
                std::string itemTitle; 
                std::cout << " Write the item title: ";
                std::cin.ignore();
                std::getline(std::cin, itemTitle); 

                // llamamos a la funcion
                Item* foundItem = searchItem(itemTitle);

                if (foundItem != nullptr) {
                    
                    std::cout << "Book found : " << foundItem->getTitle() << std::endl;
                    
                    if (foundItem->getStatus() == true) {
                        std::cout << "\n but item is already on loan, sorry.";
                    }
                    else {
                        auto now = std::chrono::system_clock::now();
                        
                        Loan* newLoan = new Loan(foundUser, foundItem, now, now, now);

                        loans.push_back(newLoan);      
                        foundItem->setStatus(true);    
                        foundUser->incrementCount(); 
                        
                        std::cout << "\n loan successful\n";
                    }

                } else {
                    std::cout << "Item not found: \n";
                    
                }  

            } else {
                std::cout << "\n User is blocked or reached loan limit." << std::endl;
            }
        };             
//funcion auxiliar
Loan* Library::searchLoan(std::string itemTitle){

    bool foundLoan = false;
    for (Loan* l: loans){
        //encapsulo el item que esta en el getloan
      Item* d = l->getItem();
        if (d->getTitle() == itemTitle){
            return l;
        }
    }
    return nullptr;
}

 void Library::returnItem(){
      std::string inputName;
    std::cout << " User name: ";
    std::cin.ignore();
    std::getline(std::cin, inputName);
    User* foundUser = searchUser(inputName);

    if (foundUser == nullptr) {
        std::cout << " User not found in the system." << std::endl;
        return;
    }
    
        std::string itemTitle; 
        std::cout << " Write the item title that wants to return: ";
        std::cin.ignore();
        std::getline(std::cin, itemTitle); 

                // llamamos a la funcion
                Loan* foundLoan = searchLoan(itemTitle);

                if (foundLoan != nullptr) {
                    
                //    std::cout << "Loan found : " << foundLoan->getTitle() << std::endl;
                    
               // que desmadre es esto, apuntador a prestamo que tiene atributo del item del prestamo encontrado, dentro de este item ves el status
                    if (foundLoan->getItem()->getStatus() == true) {
                    std::cout << "Item is already in library \n";
                    }
                    else {
                        auto now = std::chrono::system_clock::now();
                      
                        foundUser->decrementCount(); 
                      //  to do destruye el prestamo de la lista
                        std::cout << "\n return item successful\n";
                    }

                } else {
                    std::cout << "Item not found: \n";
                    
                }  


 }
   
void Library::addUser(){

std::string newUserN;
std::cout<< "Write complete username: ";
std::cin.ignore();
std::getline(std::cin, newUserN);
std::string newUserR;
std::cout << std::endl;
std::cout<< "Write rol (Estudiante, PDI or PAS): ";
std::cin.ignore();
std::getline(std::cin, newUserR);


int newId;
if (users.empty()) {
    newId = 1;
} else {
    newId = users.back()->getId() + 1;
}

User* newUser = new User(newId, newUserN, newUserR, 0);

users.push_back(newUser);

std::cout << "\nId: " << newId << "\nNew user: " << newUserN << " rol: " << newUserR << std::endl;
}

void Library::deleteUser(){

    std::string userDelete;
    std::cout << " write complete username of the person that you want to delete :";
    std::cin.ignore();
    std::getline(std::cin, userDelete);

User* foundUser = searchUser(userDelete);
 if (foundUser == nullptr) {
        std::cout << " User not found in the system." << std::endl;
        return;
    }
    if (foundUser->getCount() != 0){
        std::cout<<"imposible to delete, user has loans in their name.\n";
        return;

    } else{
        std::cout<< " sure that you want to delete user "<< userDelete << " ? (yes/no): ";
        std::string choise;
        std::getline(std::cin, choise);
        if (choise == "yes"||choise == "Yes"||choise == "y"||choise == "Y"){
   for (auto it = users.begin(); it != users.end(); ++it) {
            if (*it == foundUser) { 
                
            
                delete foundUser; 
                
                users.erase(it); 
                
                std::cout << "User deleted successfully.\n";
                return; 
            }
        }
     }
   }
};

void Library::modifiedUser(){
    
    std::string userMod;
    std::cout << " write complete username of the person that you want to modify: ";
    std::cin.ignore();
    std::getline(std::cin, userMod);

    User* foundUser = searchUser(userMod);
    if (foundUser == nullptr) {
        std::cout << " User not found in the system." << std::endl;
        return;
    } 
    
    std::string userCha;
    std::cout << " write the characteristic that you want to change (Name, Rol): ";
    std::getline(std::cin, userCha);
    
    if (userCha == "Name" || userCha == "name") {
        std::string newName;
        std::cout << " write new name: ";
        std::getline(std::cin, newName);
        
        foundUser->setName(newName);
        std::cout << " changes done successfully\n";
        
    } else if (userCha == "Rol" || userCha == "rol") {
        std::string newRol;
        std::cout << " write new rol (Estudiante, PDI, PAS): ";
        std::getline(std::cin, newRol);
        
        if (newRol == "Estudiante" || newRol == "estudiante" || 
            newRol == "PDI" || newRol == "pdi" || 
            newRol == "PAS" || newRol == "pas") {
            foundUser->setRol(newRol);
            std::cout << " changes done successfully\n";
        } else {
            std::cout << "Invalid Rol.\n";
        }
        
    } else {
        std::cout << "Invalid option.\n";
    }
}

void Library::addItem(){
    
    std::cout << " Write the title of the new item: ";
    std::cin.ignore();
    std::string newItemName;
    std::getline(std::cin, newItemName);

    Item* foundItem = searchItem(newItemName);

    if (foundItem != nullptr) {
        std::cout << "Item is already in catalog" << std::endl;
        return;
    }
    
    std::cout << "  Write the author name: ";
    std::string newItemAuthor;
    std::getline(std::cin, newItemAuthor);
    
    int newId;
    if (catalog.empty()) {
        newId = 1;
    } else {
        newId = catalog.back()->getId() + 1;
    }

    std::cout << "  Write the category: ";
    std::string newItemcategory;
    std::getline(std::cin, newItemcategory);

    std::cout << " Write item type (Book, Journal, Ebook): ";
    std::string newItemtype;
    std::getline(std::cin, newItemtype);
    
    if (newItemtype != "Book" && newItemtype != "book" && 
        newItemtype != "Journal" && newItemtype != "journal" && 
        newItemtype != "Ebook" && newItemtype != "ebook") {
        std::cout << "You cannot save that type of Item\n";
        return;
    }

    Item* newItem = nullptr;

    if (newItemtype == "Book" || newItemtype == "book") {
        
        newItem = new Book(newId, newItemName, newItemAuthor, newItemcategory, false);
    } else if (newItemtype == "Journal" || newItemtype == "journal") {
        
        newItem = new Journal(newId, newItemName, newItemAuthor, newItemcategory, false);
    } else if (newItemtype == "Ebook" || newItemtype == "ebook") {

        std::cout << " Write license (EB01): ";
        std::string newEbookli;
        std::getline(std::cin, newEbookli);

        std::cout << " Write expiration date (YYYY-MM-DD): ";
        std::string dateStr;
        std::getline(std::cin, dateStr);
        
       
        std::tm tm = {};
        std::istringstream ss(dateStr);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        
     
        std::time_t time = std::mktime(&tm);
        std::chrono::system_clock::time_point newEbookex = std::chrono::system_clock::from_time_t(time);
        
        newItem = new Ebook(newId, newItemName, newItemAuthor, newItemcategory, false, newEbookli, newEbookex);
    }

    if (newItem != nullptr) {
        catalog.push_back(newItem);
        std::cout << "\nItem creation complete\n";
    } else {
        std::cout << " Failed to create item (unknown type or missing subclass definitions)\n";
    }
}

void Library::deleteItem(){

    std::string itemDelete;
    std::cout << " write complete title name of the item that you want to delete :";
    std::cin.ignore();
    std::getline(std::cin, itemDelete);

    Item* foundItem = searchItem(itemDelete);

    if (foundItem == nullptr) {
        std::cout << "Item not found.\n";
        return;
    }
    
    if (foundItem->getStatus() == true) {
        std::cout << "Item found : " << foundItem->getTitle() << std::endl;
        std::cout << "\n but item is already on loan, you can not delete yet.\n";
        return;
    }
    
    // Item exists and is not on loan
    std::cout << " are you sure that you want to delete " << itemDelete << " (Y/N)? ";
    std::string sureDelete;
    std::getline(std::cin, sureDelete);

    if (sureDelete == "Y" || sureDelete == "y" || sureDelete == "Yes" || sureDelete == "yes") {
        for (auto it = catalog.begin(); it != catalog.end(); ++it) {
            if (*it == foundItem) { 
                catalog.erase(it);      
                delete foundItem;        
                std::cout << "Item deleted successfully.\n";
                return;
            }
        }
    } else {
        std::cout << "Deletion cancelled.\n";
    }
}

 void Library::modifiedItem(){

    std::string itemMod;
    std::cout << " write complete title of the item that you want to modify: ";
    std::cin.ignore();
    std::getline(std::cin, itemMod);

    Item* foundItem = searchItem(itemMod);
    if (foundItem == nullptr) {
        std::cout << " title not found in the system." << std::endl;
        return;
    } 
    

    std::cout << " write the characteristic that you want to change (title, author, category): ";
    std::string itemCha;
    std::getline(std::cin, itemCha);
    
    if (itemCha == "Title" || itemCha == "title") {
        std::string newTitle;
        std::cout << " write new title (Manual de fotografia urbana): ";
        std::getline(std::cin, newTitle);
        
        foundItem->setTitle(newTitle);
        std::cout << " changes done successfully\n";
        
    } else if (itemCha == "author" || itemCha == "Author") {
        std::string newAuthor;
        std::cout << " write new author (Lidia Ferrer): ";
        std::getline(std::cin, newAuthor);
    
        foundItem->setAuthor(newAuthor);
        std::cout << " changes done successfully\n";
        
    } else if (itemCha == "category" || itemCha == "Category") {
        std::string newCategory;
        std::cout << " write new category (Historia): ";
        std::getline(std::cin, newCategory);
    
        foundItem->setCategory(newCategory);
        std::cout << " changes done successfully\n";
        
    } else {
        std::cout << "Invalid option.\n";
    }
};



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

void Library::ItemMenu(){

    bool exitProgram = false;

    while (!exitProgram) {
     clearConsole();
    std::cout << R"(

=======================================================
|                  ITEM MANAGEMENT MENU              |
=======================================================

 [1] Add New Item
 [2] Remove Existing Item
 [3] Edit Item Details

 [0] Return to Main Menu

-------------------------------------------------------
 Choose an option (0–3) and press ENTER:
=======================================================

)";

    int subChoice;
    std::cin >> subChoice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue; 
        }
      
        switch (subChoice) {
            case 1:
                Library::addItem();
                break;
            case 2:
                Library::deleteItem();
                break;
            case 3:
                Library::modifiedItem();
                break;
            case 0:
                std::cout << "saving data...\n";
                // Filesystem::save...
                exitProgram = true;
                break;
            default:
                std::cout << "Not valid option.\n";
                 pauseConsole();
        }
    }

}; 




void Library::userMenu(){

    bool exitProgram = false;

    while (!exitProgram) {
     clearConsole();
    std::cout << R"(

=======================================================
|                 USER MANAGEMENT MENU               |
=======================================================

 [1] Add New User
 [2] Delete User
 [3] Modified User

 [0] Return to Main Menu

-------------------------------------------------------
 Choose an option (0–3) and press ENTER:
=======================================================

)";

    int subChoice;
    std::cin >> subChoice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue; 
        }
      
        switch (subChoice) {
            case 1:
                Library::addUser();
                break;
            case 2:
                Library::deleteUser();
                break;
            case 3:
                Library::modifiedUser();
                break;
            case 0:
                std::cout << "saving data...\n";
                // Filesystem::save...
                exitProgram = true;
                break;
            default:
                std::cout << "not valid option.\n";
                 pauseConsole();
        }
    }

}; 


void Library::LoanrMenu(){

    bool exitProgram = false;

    while (!exitProgram) {
     clearConsole();
       std::cout << R"(

=======================================================
|                  LOAN SERVICES MENU                |
=======================================================

 [1] Loan an Item
 [2] Return an Item

 [0] Return to Main Menu

-------------------------------------------------------
 Choose an option (0–2) and press ENTER:
=======================================================

)";

    int subChoice;
    std::cin >> subChoice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue; 
        }
      
        switch (subChoice) {
            case 1:
                Library::doLoan();
                break;
            case 2:
                Library::returnLoan();
                break;
            case 0:
                std::cout << "saving data...\n";
                // Filesystem::save...
                exitProgram = true;
                break;
            default:
                std::cout << "not valid option.\n";
                 pauseConsole();
        }
    }

}; 

void Library::searchMenu(){

    bool exitProgram = false;

    while (!exitProgram) {
     clearConsole();
    std::cout << R"(

=======================================================
|                SEARCH & BROWSE MENU                |
=======================================================

 [1] Search by Author
 [2] Search by Title
 [3] Search by category


 [0] Return to Main Menu

-------------------------------------------------------
 Choose an option (0–2) and press ENTER:
=======================================================

)";

    int subChoice;
    std::cin >> subChoice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue; 
        }
      
        switch (subChoice) {
            case 1:
                Library::searchAuthor();
                break;
            case 2:
                Library::searchTitle();
            case 3:
                Library::searchCategory();
                break;
            case 0:
                std::cout << "saving data...\n";
                // Filesystem::save...
                exitProgram = true;
                break;
            default:
                std::cout << "not valid option.\n";
                 pauseConsole();
        }
    }

}; 



void Library::cleanAll(){
    std::cout << "cleaning memory...\n";

    //  Borrar los Préstamos
    
    for( auto const i : loans){
        delete i;
    }
    loans.clear();

    //  Borrar los Usuarios
    for (User* i : users) {
        delete i;
    }
    users.clear();

    //  Borrar el Catálogo (Items)
    for (Item* i : catalog) {
        delete i; 
    }
    catalog.clear();
    
    std::cout << "Correctly memmory cleaning\n";
}