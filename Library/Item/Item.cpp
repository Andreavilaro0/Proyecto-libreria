#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include"Item.h"


Item::Item(int _id, std::string _title, std::string _author, std::string _category, bool _status){
    id = _id;
    title = _title;
    author = _author;
    category = _category;
    status = _status;

};
  

    int Item::getId(){
        return id;
    }
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

   void Item::setStatus(bool _status){
        status = _status;

    }

    void Item::setTitle(std::string _title){
        title = _title;
    }

      void Item::setCategory(std::string _category){
        category = _category;
      }
    void Item::setAuthor(std::string _author){
        author = _author;
    }
                     


