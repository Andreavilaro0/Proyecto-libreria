

#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "../User/User.h" 
#include "../Item/Item.h"
#include "Loan.h"

Loan::Loan(User* _user, Item* _item, std::chrono::system_clock::time_point _startDay, std::chrono::system_clock::time_point _deadline, std::chrono::system_clock::time_point _returnDay){

    user = _user;
    item = _item;
    startDay = _startDay;
    deadline = _deadline;
    returnDay = _returnDay;
    
};

// Los getters están definidos inline en Loan.h
   
   