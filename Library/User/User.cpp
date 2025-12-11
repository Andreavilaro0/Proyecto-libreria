
#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "User.h"


User::User(int _id,std::string _name,std::string _rol,int _count){
    id = _id;
    name = _name;
    rol = _rol;
    count = _count;
    
};

    int  User::getId(){
        return id;
    }

    std::string User::getNme(){
        return name;
    };

    std::string User::getRol(){
        return rol;
    };
    int User::getCount(){
        return count;
    }

    int User::incrementCount() {
    count++; 
}

int User::decrementCount() {
    if (count > 0) {
        count--;
    }