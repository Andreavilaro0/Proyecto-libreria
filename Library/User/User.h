
#include<string>
#include<iostream>
#include<vector>
#include<chrono>
#include<algorithm>

class User{

    private:
    int id;
    std::string name, rol;
    int count;
    
    public:
    incrementCount();
    decrementCount();
    bool canBorrow();
    
    User(){};
    User(int, std::string,std::string, int);

    int getId();
    std::string getNme();
    std::string getRol();
    int getCount();


};