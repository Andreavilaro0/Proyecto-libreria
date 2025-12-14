#ifndef BOOK_H
#define BOOK_H

#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include"Item.h"


class Book : public Item {
    private:
  
    public:
        Book(){};
        Book(int id, std::string title, std::string author, std::string category, bool status)
            : Item(id, title, author, category, status) {}
        
        std::string info() override {
            return "Book: " + getTitle() + " by " + getAuthor();
        }
};

#endif // BOOK_H