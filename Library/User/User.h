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

  int getId() const;
  void setName(const std::string& newNamec);
  void setRol(const std::string& newRol);
  std::string getName() const;
  std::string getRol() const;
  int getCount() const;
};

#endif // USER_H
