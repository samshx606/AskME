#include <bits/stdc++.h>
#include "User.h"
#include "question.h"
#include "answer.h"
using namespace std;
string user_path = R"(C:\Users\VI$ION\Desktop\Projects\oop\AskMe project\users.txt)";
string question_path = R"(C:\Users\VI$ION\Desktop\Projects\oop\AskMe project\questions.txt)";
string answer_path = R"(C:\Users\VI$ION\Desktop\Projects\oop\AskMe project\answers.txt)";
string user_id_path = R"(C:\Users\VI$ION\Desktop\Projects\oop\AskMe project\user_id.txt)";
string question_id_path = R"(C:\Users\VI$ION\Desktop\Projects\oop\AskMe project\question_id.txt)";
string answer_id_path = R"(C:\Users\VI$ION\Desktop\Projects\oop\AskMe project\answer_id.txt)";
vector<User> users;
vector<question> questions;
vector<answer> answers;
User cur_user;
vector<string> split_string(string s, const string& delimiter = ",") {
    vector<string> strs;

    int pos = 0;
    string substr;
    while ((pos = (int) s.find(delimiter)) != -1) {
        substr = s.substr(0, pos);
        strs.push_back(substr);
        s.erase(0, pos + delimiter.length());
    }
    strs.push_back(s);
    return strs;
}
void load_users(){
    ifstream user_in(user_path);
    if(user_in.fail()){
        cout<<"Can't open user file\n";
    }
    string substr;
    while (getline(user_in , substr)){
        vector<string> user = split_string(substr);
        int id = stoi(user[0]);
        string name = user[1];
        string username = user[2];
        string pass = user[3];
        users.emplace_back(id,name,username,pass);
    }
    user_in.close();
}
void load_questions(){
    ifstream question_in(question_path);
    if(question_in.fail()){
        cout<<"can't open question file\n";
    }
    string substr;
    while (getline(question_in , substr)){
        vector<string>question = split_string(substr);
        int id = stoi(question[0]);
        string from = question[1];
        string to = question[2];
        bool state = (question[3][0] - '0');
        string text = question[4];
        questions.emplace_back(id,from,to,state,text);
    }
}
void load_answers(){
    ifstream answer_in(answer_path);
    if(answer_in.fail()){
        cout<<"can't open question file\n";
    }
    string substr;
    while (getline(answer_in , substr)){
        vector<string>answer = split_string(substr);
        int id = stoi(answer[0]);
        int question_id = stoi(answer[1]);;
        string text = answer[2];
        answers.emplace_back(id,question_id,text);
    }
}
int user_id(){
    int id;
    ifstream id_in(user_id_path);
    if(id_in.fail()){
        cout<<"Can't open id file\n";
    }
    id_in>>id;
    id++;
    id_in.close();
    ofstream id_out(user_id_path);
    if(id_out.fail()){
        cout<<"Can't open id file\n";
    }
    id_out<<id;
    id_out.close();
    return id;
}
int question_id(){
    int id;
    ifstream id_in(question_id_path);
    if(id_in.fail()){
        cout<<"Can't open question id file";
    }
    id_in >>id;
    id_in.close();
    id++;
    ofstream id_out(question_id_path);
    if(id_out.fail()){
        cout<<"Can't open question id file";
    }
    id_out << id;
    id_out.close();
    return id;
}
int answer_id(){
    int id;
    ifstream id_in(answer_id_path);
    if(id_in.fail()){
        cout<<"Can't open question id file";
    }
    id_in >>id;
    id_in.close();
    id++;
    ofstream id_out(answer_id_path);
    if(id_out.fail()){
        cout<<"Can't open question id file";
    }
    id_out << id;
    id_out.close();
    return id;
}
void print_question_to_me(){
    int count = 1;
    for (auto & question : questions) {
        if(cur_user.get_username() == question.get_to_user()){
            if(!question.get_state()){
                cout<<"\t"<<count<<"- \""<<question.get_from_user()<<"\" asked you \""<<question.get_text()<<"\"\n";
            }else{
                cout<<"\t"<<count<<"- unknown person asked you \""<<question.get_text()<<"\"\n";
            }
            int c = 1;
            for (auto & answer : answers) {
                if(question.get_id() == answer.get_question_id()){
                    cout<<"\t\t-Your answer: "<<answer.get_text()<<"\n";
                    c = 0;
                }
            }
            if(c){
                cout<<"\t\t-You didn't answer yet\n";
            }
            count++;
        }
    }
    if(count == 1){
        cout<<"\tThere is no questions for you\n";
    }
}
void print_question_from_me(){
    int count = 1;
    for (auto & question : questions) {
        if(cur_user.get_username() == question.get_from_user()){
            cout<<"\t"<<count<<"- You asked \""<<question.get_to_user()<<"\" \""<<question.get_text()<<"\"\n";
            int c = 1;
            for (auto & answer : answers) {
                if(answer.get_question_id() == question.get_id()){
                    cout<<"\t\t- His answer: \""<<answer.get_text()<<"\"\n";
                    c = 0;
                }
            }
            if(c){
                cout<<"\t\t- He didn't answer yet.";
            }
            count++;
        }
    }
    if(count == 1){
        cout<<"\tThere is no questions from you\n";
    }
}
void answer_question(){
    cout<<"Enter question id you want to answer or 0 to exist: ";
    string answer_text;
    int question_id;
    while (1){
        cin>>question_id;
        if(question_id == 0){
            return;
        }
        int c = 0 , check_answered = 0;
        for (auto question :questions) {
            if(question_id == question.get_id() && cur_user.get_username() == question.get_to_user()){
                c = 1;
            }
        }
        for (auto & answer : answers) {
            if(answer.get_question_id() == question_id){
                check_answered = 1;
                break;
            }
        }
        if(c && !check_answered){
            break;
        }else if(c){
            cout<<"This question you answered before, Enter question id again or 0 to exist: ";
        }else{
            cout<<"Can't find such question, Enter question id again or 0 to exist: ";
        }
    }
    cout<<"Enter Your answer: ";
    getline(cin>>ws , answer_text);
    int id = answer_id();
    ofstream answer_out(answer_path , ios::app);
    if(answer_out.fail()){
        cout<<"Can't open answer file\n";
    }
    answer_out << id<<","<<question_id<<","<<answer_text<<"\n";
    answer_out.close();
    answers.emplace_back(id,question_id,answer_text);
}
void delete_question(){
    cout<<"Enter question id or 0 to exist: ";
    while (1){
        int id,check_question=0,check_answer=0;
        cin>>id;
        if(id == 0){
            break;
        }
        for(auto question=questions.begin() ; question < questions.end() ; question++){
            if(question->get_id() == id && cur_user.get_username() == question->get_from_user()){
                for(auto answer = answers.begin() ; answer < answers.end() ; answer++){
                    if(question->get_id() == answer->get_question_id()){
                        answers.erase(answer);
                        check_answer = 1;
                        break;
                    }
                }
                questions.erase(question);
                check_question = 1;
                break;
            }
        }
        if(check_question){
            ofstream question_out(question_path);
            if(question_out.fail()){
                cout<<"Can't open question file\n";
            }
            for (auto & question : questions) {
                question_out << question.get_id()<<","<<
                             question.get_from_user()<<","<<
                             question.get_to_user()<<","<<
                             question.get_state()<<","<<
                             question.get_text()<<"\n";
            }
        }
        if(check_answer){
            ofstream answer_out(answer_path);
            if(answer_out.fail()){
                cout<<"Can't open question file\n";
            }
            for (auto & answer : answers) {
                answer_out << answer.get_id()<<","<<answer.get_question_id()<<","<<answer.get_text()<<"\n";
            }
        }
        if(check_question){
            cout<<"You have deleted your question.\n\n";
            break;
        }else{
            cout<<"Can't find such question, Enter again or 0 to exist: ";
        }
    }

}
void delete_answer(){
    cout<<"Enter answer id or 0 to exist: ";
    while (1){
        int id,check_answer=0;
        cin>>id;
        if (id == 0){
            break;
        }
        for(auto answer = answers.begin() ; answer < answers.end() ; answer++){
            if(id == answer->get_id()){
                for (auto & question : questions) {
                    if(answer->get_question_id() == question.get_id()){
                        if(cur_user.get_username() == question.get_to_user()){
                            answers.erase(answer);
                            check_answer = 1;
                        }
                        break;
                    }
                }
                break;
            }
        }
        if(check_answer){
            ofstream answer_out(answer_path);
            if(answer_out.fail()){
                cout<<"Can't open question file\n";
            }
            for (auto & answer : answers) {
                answer_out << answer.get_id()<<","<<answer.get_question_id()<<","<<answer.get_text()<<"\n";
            }
            cout<<"Answer deleted!\n";
            break;
        }else{
            cout<<"invalid id, Enter again or 0 to exist: ";
        }
    }
}
void ask_question(){
    string question , asked_user;
    bool state;
    cout<<"- Enter username you want to ask: ";
    while (1){
        cin>>asked_user;
        int check_user = 0;
        for (auto & User : users) {
            if(asked_user == User.get_username() && asked_user != cur_user.get_username()){
                check_user = 1;
            }
        }
        if(check_user){
            break;
        }else{
            cout<<"Can't find such user, Enter again: ";
        }
    }
    cout<<"- Enter your question: ";
    getline(cin>>ws , question);
    cout<<"- do you want ask anonymous\n";
    cout<<"\t1: yes\n";
    cout<<"\t0: no\n";
    cin>>state;
    int id=question_id();

    ofstream question_out(question_path , ios::app);
    if(question_out.fail()){
        cout<<"can't open question file\n";
    }

    question_out << id << "," << cur_user.get_username()<<","<<asked_user<<","<<state<<","<<question<<"\n";
    question_out.close();
    questions.emplace_back(id,cur_user.get_username(),asked_user,state,question);
    cout<<"- Question is asked successfully\n";
}
void list_system_user(){
    cout<<"- There's "<<users.size()<<" users in the system\n";
    int count = 1;
    for (auto & User : users) {
        cout<<"\t"<<count<<"- "<<User.get_username()<<"\n";
        count++;
    }
}
void feed(){
    for (int i = 0; i < questions.size(); ++i) {
        if(questions[i].get_state()){
            cout<<"\t"<<i+1<<"- \"Unknown person"<<"\" asked \""<<questions[i].get_to_user()<<"\" \""<<questions[i].get_text()<<"\"\n";
        }else{
            cout<<"\t"<<i+1<<"- \""<<questions[i].get_from_user()<<"\" asked \""<<questions[i].get_to_user()<<"\" \""<<questions[i].get_text()<<"\"\n";
        }
        int check_answer = 1;
        for (int j = 0; j < answers.size(); ++j) {
            if(questions[i].get_id() == answers[j].get_question_id()){
                cout<<"\t\t- \""<<questions[i].get_to_user()<<"\" answered \""<<answers[j].get_text()<<"\"\n";
                check_answer = 0;
                break;
            }
        }
        if(check_answer){
            cout<<"\t\t- \""<<questions[i].get_to_user()<<"\" didn't answer yet\n";
        }
    }
}
void show_menu(){
    string val;
    cout<<"\n Menu\n";
    cout<<"\t1: Print question to me\n";
    cout<<"\t2: Print question from me\n";
    cout<<"\t3: Answer question\n";
    cout<<"\t4: Delete question\n";
    cout<<"\t5: Ask question\n";
    cout<<"\t6: Delete answer\n";
    cout<<"\t7: List system user\n";
    cout<<"\t8: Feed\n";
    cout<<"\t9: Logout\n";
    cout<<"Enter number in range 1-8: ";
    while (1){
        cin>>val;
        if(val>="1" && val<="9"){
            break;
        }
        cout<<"wrong value, Try again\n";
    }
    if(val == "1"){
        print_question_to_me();
    }else if(val == "2"){
        print_question_from_me();
    } else if(val == "3"){
        answer_question();
    }else if(val == "4"){
        delete_question();
    }else if(val == "5"){
        ask_question();
    }else if(val == "6"){
        delete_answer();
    }else if(val == "7"){
        list_system_user();
    }else if(val == "8"){
        feed();
    }
    if(val == "9"){
        cout<<"- You have logged out!\n\n";
        return;
    }else{
        return show_menu();
    }
}
void Register(){
    string name,username,password;
    cout<<"Enter name or 0 to exist: ";
    getline(cin>>ws , name);
    if(name == "0"){
        return;
    }
    cout<<"Enter username or 0 to exist: ";
    while (1){
        cin>>username;
        if(username == "0"){
            return;
        }
        int c = 1;
        for (auto & User : users) {
            if(User.get_username() == username){
                c = 0;
                break;
            }
        }
        if(c){
            break;
        }else{
            cout<<"PLease enter another username or 0 to exist: ";
        }
    }
    cout<<"Password\n";
    while (1){
        cout<<"\t-Password length should be more than 5 chars.\n\t";
        cout<<"-Password should contain en letters and numbers.\nEnter password or 0 to exist: ";
        cin>>password;
        if(password == "0"){
            return;
        }
        int check_yes = 0 , check_no = 1;
        int check_num = 0 , check_char = 0;
        for (int i = 0; i < password.size(); ++i) {
            if((password[i]>='A' && password[i] <= 'Z') ||(password[i] >= 'a' && password[i] <= 'z') ){
                check_char = 1;
            }
            if(password[i] >= '0' && password[i] <= '9'){
                check_num = 1;
            }
            if((password[i]<'A' || password[i] > 'Z') && (password[i] < 'a' || password[i]>'z') && (password[i]<'0' || password[i] > '9')){
                check_no = 0;
            }
        }
        if(check_char&&check_num){
            check_yes = 1;
        }
        if(check_no && check_yes && password.size()>=5){
            break;
        }else{
            cout<<"Invalid Password!!\n";
        }
    }
    ofstream user_out(user_path , ios::app);
    int id = user_id();
    user_out <<id << ","<< name << ","<< username << "," << password <<'\n';
    user_out.close();
    users.emplace_back(id,name,username,password);
    cout<<"\nYour account has been created\n\n";
}
void login(){
    string user,pass;
    while (1){
        cout<<"- enter username or 0 to exist: ";
        cin>>user;
        if(user == "0"){
            return;
        }
        cout<<"- enter password or 0 to exist: ";
        cin>>pass;
        if(pass == "0"){
            return;
        }
        int c = 1;
        for (auto & User : users) {
            if(user==User.get_username() && pass == User.get_password()){
                cur_user = User;
                c = 0;
                break;
            }
        }
        if(c){
            cout<<"Invalid username or password, try again\n\n";
        }else{
            break;
        }
    }
    show_menu();

}
void Run_System(){
    load_users();
    load_questions();
    load_answers();
    cout<<"\n\t\t\t\t\tWelcome To AskMe Project\n";
    while (1){
        string inp;
        cout<<"- Menu\n\t1: Login\n\t2: Register\n\t0: Exist\nPlease answer in range 0-2: ";
        cin>>inp;
        if(inp == "1"){
            login();
        }else if(inp == "2"){
            Register();
        }else if(inp == "0"){
            break;
        }else{
            cout<<"- Please Enter Valid Input\n";
        }
    }
}
int main(){
    Run_System();
}