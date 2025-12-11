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

public:
  User() {};
  User(int, std::string, std::string, int);

  void incrementCount();
  void decrementCount();
  bool canBorrow();

  int getId();
  std::string getNme();
  std::string getRol();
  int getCount();
};

#endif // USER_H
