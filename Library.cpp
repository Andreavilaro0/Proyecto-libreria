#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "Library.h"
#include "User/User.h"   
#include "Item/Item.h"  
#include "Loan/Loan.h"


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


Library::Library(std::vector<Item*> _catalog, std::vector<User*> _users, std::vector<Loan*> _loans){
    catalog = _catalog;
    users = _users;
    loans = _loans;
};

    void search(); //tittle
    void search(); //date
    void search(); //objet
    void loan();
    void santion();
    void addUser();
    void deleteUser();
    void modifiedUser();
    void blockUser();
    void addItem();
    void deleteItem();
    void modifiedItem();
    void returnLoan();
    void checkLoan();



    Item* item = new Item()

    vector.push_back(item);
    v.at[i]->




 void Library::searchAuthor(){ //author
std::string selectAuthor;
std::vector<Item*>filter;
 
clearconsole();
std::cout << " write the author that you want to search :";
std::getline(std::cin, selectAuthor);
for (const auto& authorTosearch : catalog) {
    if (authorTosearch->getAuthor()== selectAuthor){
        filter.push_back(authorTosearch);
    }
};
   
std::cout << "  ════════════════════════════════════════\n";
std::cout<< "  SEARCH BY AUTHOR :" << selectAuthor<<std::endl;
std::cout << "  ════════════════════════════════════════\n";

for (const auto& authorTosearch : filter){
std::cout<< "  "<<authorTosearch->getAuthor()<<std::endl;
};

pauseConsole();
vector.clear;
clearConsole();
} 

void Library::searchTitle(){

std::string selectTitle;
std::vector<Item*>filter;
 
clearconsole();
std::cout << " write the title that you want to search :";
std::getline(std::cin, selectTittle);
for (const auto& tittleTosearch : catalog) {
    if (authorTosearch->getTitle()== selectTitle){
        filter.push_back(titleTosearch);
    }
};
   
std::cout << "  ════════════════════════════════════════\n";
std::cout<< "  SEARCH BY TITLE :" << selectAuthor<<std::endl;
std::cout << "  ════════════════════════════════════════\n";

for (const auto& titleTosearch : filter){
std::cout<< "  "<<titleTosearch->getTitle()<<std::endl;
};

pauseConsole();
vector.clear;
clearConsole();
} 

void Library::searchCategory(){

std::string selectCategory;
std::vector<Item*>filter;
 
clearconsole();
std::cout << " write the category that you want to search :";
std::getline(std::cin, selectCategory);
for (const auto& categoryTosearch : catalog) {
    if (CategoryTosearch->getCategory()== selectCategory){
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
vector.clear;
clearConsole();
} //tittle

//funcion auxiliar
Item* Library::searchItem(std::string itemTitle){
     
    bool foundItem = false;  
    for(item* item : catalog){
     if (item->getTitle() == itemTitle){
        return item;       
     } 
    } 
    return nullptr;
  };
  

 void Library::doLoan() {
  
    clearconsole(); 
 
    std::string inputName;
    std::cout << " User name: ";
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
Loan* Library::searchLoan(std::string itemLoan){

    bool foundLoan = false;
    for (Loan* loan : loans){
        if (loan->getLoan() == itemLoan){
            return loan;
        }
    }
    return nullptr;
}

 void library::returnLoan(){
      std::string inputName;
    std::cout << " User name: ";
    std::getline(std::cin, inputName);

    User* foundUser = searchUser(inputName);

    if (foundUser == nullptr) {
        std::cout << " User not found in the system." << std::endl;
        return;
    }
    
                 std::string itemTitle; 
                std::cout << " Write the item title that wants to return: ";
                std::getline(std::cin, loanTittle); 

                // llamamos a la funcion
                Item* foundLoan = searchLoan(loanTitle);

                if (foundItem != nullptr) {
                    
                //    std::cout << "Loan found : " << foundLoan->getTitle() << std::endl;
                    
                
                    if (foundItem->getStatus() == true) {
                        
                       for (Loan* x :loans ){
                        of (foundItem)
                       }

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


 }
   


   void santion(){
 
    // ir a lista de prestamos y comparar fecha de prestamo con expiracion
    // si ha pasado OR mas de 14 dias de la fecha que se lleva ( logica de sansion)


   };

   void addUser(){

std::string newUser
std::cout<< "Write complete username: ";
std::getline(cin, newUser);
std::cout<< endl;
std::string newUserR;
std::cout<< "Write rol (estudent,  , ): ";
std::cin>>newUserR;
std::cout<< endl;

//logica escribir user en cvs

   }



void deleteUser(){

    std::string userDe;
    std::cout << " write complete username of the person that you want to delete :";
    std::getline(cin, userDe);

    //comparar existencia de user y si esta borrar, si no dar erro y obcion salir o intentard de nuevo
}

void modifiedUser(){
    
}