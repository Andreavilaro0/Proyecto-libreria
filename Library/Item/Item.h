#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

class Item {

private:
  int id;
  std::string title, author, category;
  bool status = false;

public:
  Item() {};
  Item(int, std::string, std::string, std::string, bool);
  virtual std::string info() = 0;

  int getId()const;
  std::string getTitle()const;
  std::string getAuthor()const;
  std::string getCategory()const;
  bool getStatus()const;

  void setStatus(bool _status);
  void setTitle(std::string _title);
   void setAuthor(std::string _author);
    void setCategory(std::string _category);
};

#endif // ITEM_H
