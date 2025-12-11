
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

int User::decrementCount(){
    if (count > 0) {
        count--;
    }
}

  bool User::canBorrow() {
 
    if (rol == "Estudiante" && count < 3) {
        return true;
    }
    if (rol == "PDI" && count < 6) {
        return true;
    }
    if (rol == "PAS" && count < 5) {
        return true;
    }
    // Si no entró en ningún if anterior, es que no puede pedir prestado.
    return false; 
}