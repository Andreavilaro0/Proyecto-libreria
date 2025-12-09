#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include"Item.h"
#include"E-book.h"


Ebook::Ebook(int _id, std::string _title, std::string _author, std::string _category, bool _status, std::string _license, std::chrono::system_clock::time_point _expiration) : Item(_id, _title, _author, _category, _status){

    license = _license;
    expiration = _expiration;
};

