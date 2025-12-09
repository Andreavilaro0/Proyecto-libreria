
#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "Library/User/User.h"
#include "Library/Item/Item.h"
#include "Library/Loan/Loan.h"


class Library{
    private:
    std::vector<Item*> catalog;
    std::vector<User*> users;
    std::vector<Loan*> loans;

    public:
    Library(){};
    
    Library(std::vector<Item*> catalog, std::vector<User*> users, std::vector<Loan*> loans);
    
    void searh(); //author
    void searh(); //tittle
    void searh(); //date
    void searh(); //objet
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




};