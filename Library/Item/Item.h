
#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>

class Item{

    private:
    int id;
    std::string title,author,category;
    bool status = false;

    public:
    Item(){};
    Item(int, std::string,std::string,std::string, bool);
    virtual std::string info() = 0;

    std::string getTitle();
    std::string getAuthor();
    std::string getCategory();
    bool getStatus();

};