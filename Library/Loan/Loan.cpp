
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

  Item* Loan::getItem()const{
    return item;
  }
  
  User* Loan::getUser()const{
    return user;
  }
  

  std::chrono::system_clock::time_point Loan::getStartDay() {
    return startDay;
}
std::chrono::system_clock::time_point Loan::getDeadline() {
    return deadline;
}
std::chrono::system_clock::time_point Loan::getreturnDay() {
    return returnDay;
}
   

//al final ni lo use
std::ostream& operator<<(std::ostream& os, const Loan& loan) {
    std::string userName = (loan.user != nullptr) ? loan.user->getName() : "uknow User";
    std::string itemTitle = (loan.item != nullptr) ? loan.item->getTitle() : "uknow Item";


    os << userName << " has loan " << itemTitle;
  
    return os;
}