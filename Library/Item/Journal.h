#ifndef JOURNAL_H
#define JOURNAL_H

#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include"Item.h"


class Journal : public Item {
    private:
  
    public:
        Journal(){};
        Journal(int id, std::string title, std::string author, std::string category, bool status)
            : Item(id, title, author, category, status) {}
        
        std::string info() const override {
            return "Journal: " + getTitle() + " by " + getAuthor();
        }
};

#endif // JOURNAL_H