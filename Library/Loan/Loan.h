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
  Loan() {};
  Loan(User*, Item *, std::chrono::system_clock::time_point,
       std::chrono::system_clock::time_point,
       std::chrono::system_clock::time_point);

  // Getters
  User* getUser() const { return user; }
  Item* getItem() const { return item; }
  std::chrono::system_clock::time_point getStartDay() const { return startDay; }
  std::chrono::system_clock::time_point getDeadline() const { return deadline; }
  std::chrono::system_clock::time_point getReturnDay() const { return returnDay; }
  
  void penalize();
};

#endif // LOAN_H
