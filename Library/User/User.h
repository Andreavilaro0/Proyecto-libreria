#ifndef USER_H
#define USER_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

class User {

private:
  int id;
  std::string name, rol;
  int count;
  double sanctionAmount = 0.0;

public:
  User() {};
  User(int, std::string, std::string, int, double);

  void incrementCount();
  void decrementCount();
  bool canBorrow();

  int getId();
  void setName(const std::string& newNamec);
  void setRol(const std::string& newRol);
  std::string getName();
  std::string getRol();
  int getCount();

void addSanction(double amount);
double getSanction();

void paySanction();



};

#endif // USER_H
