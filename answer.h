#include "bits/stdc++.h"
using namespace std;
#ifndef OOP_ANSWER_H
#define OOP_ANSWER_H
class answer{
    private:
        int id;
        int question_id;
        string text;
    public:
        answer(int id,int question_id,string text):
        id(id),
        question_id(question_id),
        text(text){}
        int get_id(){
            return id;
        }
        int get_question_id(){
            return question_id;
        }
        string get_text(){
            return text;
        }
};
#endif //OOP_ANSWER_H
