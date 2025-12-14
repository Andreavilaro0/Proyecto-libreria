
#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>
#include "User.h"


User::User(int _id,std::string _name,std::string _rol,int _count, double _sanctionAmount){
    id = _id;
    name = _name;
    rol = _rol;
    count = _count;
    sanctionAmount = _sanctionAmount;
    
};


void User::setName(const std::string& newName) {
    name = newName;

};

void User::setRol(const std::string& newRol){
 rol = newRol;
};

int  User::getId(){
        return id;
    }

    std::string User::getName(){
        return name;
    };

    std::string User::getRol(){
        return rol;
    };
    int User::getCount(){
        return count;
    }

    void User::incrementCount() {
    count++; 
}

void User::decrementCount(){
    if (count > 0) {
        count--;
    }
}

  bool User::canBorrow() {
  if (sanctionAmount > 10.0) {
        return false; 
    }

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
// Sumamos la nueva multa a lo que ya debía
void User::addSanction(double amount) {
    sanctionAmount += amount; 
}

double User::getSanction() {
    return sanctionAmount;
}
// Deuda saldada
void User::paySanction() {
    sanctionAmount = 0.0; 
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "ID: " << user.id << " | " << user.name << " (" << user.rol << ")";
    return os;
}