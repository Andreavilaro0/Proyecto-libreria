

#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include"Item.h"


class Ebook : public Item {
    private:
        std::string license;
        std::chrono::system_clock::time_point expiration;

    public:
        Ebook(){};
        Ebook(int id, std::string title, std::string author, std::string category, bool status, 
              std::string license, std::chrono::system_clock::time_point expiration)
            : Item(id, title, author, category, status), license(license), expiration(expiration) {}
        
        std::string info() override {
            return "Ebook: " + getTitle() + " by " + getAuthor() + " (License: " + license + ")";
        }
        
        std::string getLicense() { return license; }
        std::chrono::system_clock::time_point getExpiration() { return expiration; }
};




