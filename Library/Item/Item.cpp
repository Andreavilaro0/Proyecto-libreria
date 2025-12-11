#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include"Item.h"
#include "../Library.h";


Item::Item(int _id, std::string _title, std::string _author, std::string _category, bool _status){
    id = _id;
    title = _title;
    author = _author;
    category = _category;
    status = _status;

};
  

    std::string Item::getTitle(){
        return title;
    }
    std::string Item::getAuthor(){
        return author;
    }
    std::string Item::getCategory(){
        return category;
    }
    bool Item::getStatus(){
        return status;
    };


