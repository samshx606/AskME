#ifndef OOP_USER_H
#define OOP_USER_H
#include <bits/stdc++.h>
using namespace std;
class User {
    private:
        int id;
        string name;
        string username;
        string password;
    public:
        User(int id , string name , string username , string password):
        id(id),
        name(name),
        username(username),
        password(password){}
        int get_id(){
            return id;
        }
        User(){}
        string get_name(){
            return name;
        }
        string get_username(){
            return username;
        }
        string get_password(){
            return password;
        }
};


#endif //OOP_USER_H
