
#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "../User/User.h"
#include "../Item/Item.h"

class Loan{

    private:
   User *user;
   Item *item;
   std::chrono::system_clock::time_point startDay, deadline, returnDay;
   public:
   Loan(){};
   Loan(User*, Item*, std::chrono::system_clock::time_point, std::chrono::system_clock::time_point, std::chrono::system_clock::time_point);



};