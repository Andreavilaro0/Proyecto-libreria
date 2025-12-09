
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
     Ebook(int, std::string, std::string, std::string, bool, std::string, std::chrono::system_clock::time_point);
};



