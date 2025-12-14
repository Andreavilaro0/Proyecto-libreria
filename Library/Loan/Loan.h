#ifndef LOAN_H
#define LOAN_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "../User/User.h"
#include "../Item/Item.h"

class Loan {

private:
  User *user;
  Item *item;
  std::chrono::system_clock::time_point startDay, deadline, returnDay;
  public:
 Item* getItem()const;
 User* getUser()const;
  void penalize()const;

  Loan() {};
  Loan(User*, Item *, std::chrono::system_clock::time_point,
       std::chrono::system_clock::time_point,
       std::chrono::system_clock::time_point);

     std::chrono::system_clock::time_point getStartDay();
     std::chrono::system_clock::time_point getDeadline();
     std::chrono::system_clock::time_point getreturnDay();
};

 


#endif // LOAN_H
