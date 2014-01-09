#include <iostream>
using namespace std;

int main(){
    string pass = "password";
    string input;
    cout << "What is your password: ";
    cin >> input;
    if (input==pass){
        cout << "Correct" << endl;
    }else{
        cout << "Wrong" << endl;
    }
    return 0;
}