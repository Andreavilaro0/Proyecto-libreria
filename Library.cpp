#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "Library.h"
#include "User/User.h"   
#include "Item/Item.h"  
#include "Loan/Loan.h"


Library::Library(std::vector<Item*> _catalog, std::vector<User*> _users, std::vector<Loan*> _loans){
    catalog = _catalog;
    users = _users;
    loans = _loans;
};

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
