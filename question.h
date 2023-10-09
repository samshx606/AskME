#include "bits/stdc++.h"
using namespace std;

#ifndef OOP_QUESTION_H
#define OOP_QUESTION_H
class question{
    private:
        int id;
        string from_user;
        string to_user;
        bool state;
        string text;
    public:
        question(int id,string from_user,string to_user,bool state,string text):
        id(id),
        from_user(from_user),
        to_user(to_user),
        state(state),
        text(text){}

        int get_id(){
            return id;
        }
        string get_from_user(){
            return from_user;
        }
        string get_to_user(){
            return to_user;
        }
        bool get_state(){
            return state;
        }
        string get_text(){
            return text;
        }
};
#endif //OOP_QUESTION_H
