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
  void setName(const std::string& newNamec);
  void setRol(const std::string& newRol);
  std::string getName();
  std::string getRol();
  int getCount();
};

#endif // USER_H
