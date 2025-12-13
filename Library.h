#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "Library/User/User.h"
#include "Library/Item/Item.h"
#include "Library/Loan/Loan.h"

// Forward declarations of utility functions
void clearConsole();
void pauseConsole();
void showMenu();

class Library{
    private:
    std::vector<Item*> catalog;
    std::vector<User*> users;
    std::vector<Loan*> loans;

    public:
    Library(){};
    
    Library(std::vector<Item*> catalog, std::vector<User*> users, std::vector<Loan*> loans);
    


    void searchAuthor(); 
    void searchTitle();
    void searchDate(); //date
    void searchCategory(); 
    void doLoan();
    void santion();
    void penalize();
    void addUser();
    void deleteUser();
    void modifiedUser();
    void blockUser();
    void addItem();
    void deleteItem();
    void modifiedItem();
    void returnItem();
    void checkLoan();


//auxiliares

Item* searchItem(std::string itemTitle);
User* searchUser(std::string inputUser);
Loan* searchLoan(std::string itemLoan);
  
//submenus
void ItemMenu(); 
void userMenu();
void LoanrMenu();
void searchMenu();

//borrar memoria
 void cleanAll();

};

