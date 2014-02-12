#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

int evalRPN(vector<string> &tokens){
    stack<string> tmp;
    vector<string>::iterator it = tokens.begin();
    int a,b,num;
    for(;it!=tokens.end();++it){
        if(*it == "+" || *it=="-" || *it=="*" || *it=="/"){
            if (tmp.size()>=2){
                b = stoi(tmp.top());
                tmp.pop();
                a = stoi(tmp.top());
                tmp.pop();
                if(*it == "+"){
                    num = a+b;
                }   
                if(*it == "-"){
                    num = a-b;
                }   
                if(*it == "-"){
                    num = a-b;
                }   
                if(*it == "*"){
                    num = a*b;
                }
                if(*it == "/"){
                    num = a/b;
                }
                tmp.push(to_string(num));
            }else{
                return -1;
            }
        }else{
            tmp.push(*it);
        }
    }
    if(tmp.size()!=1){
        return -1;
    }else{
        return stoi(tmp.top());
        tmp.pop();
    }
}

int main(){
    vector<string> str={"4", "13", "5", "/", "+"};
    cout << evalRPN(str) << endl;
    return 0;
}
