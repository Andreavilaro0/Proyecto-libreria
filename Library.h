#ifndef LIBRARY_H
#define LIBRARY_H

#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "Library/User/User.h"
#include "Library/Item/Item.h"
#include "Library/Loan/Loan.h"
#include "Library/Item/E-book.h"

void clearConsole();
void pauseConsole();

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
    void searchDate(); 
    void searchCategory(); 
    void doLoan();
    void returnLoan();
    void penalize();
    void addUser();
    void deleteUser();
    void modifiedUser();
    void blockUser();
    void addItem();
    void deleteItem();
    void modifiedItem();
   


//auxiliares

Item* searchItem(std::string itemTitle);
User* searchUser(std::string inputUser);
Loan* searchLoan(std::string itemLoan);
Ebook* searchExpirationDate(std::string foundEbook);

//submenus
void ItemMenu(); 
void userMenu();
void LoanrMenu();
void searchMenu();

//borrar memoria
 void cleanAll();
 void saveAll();

};

#endif // LIBRARY_H