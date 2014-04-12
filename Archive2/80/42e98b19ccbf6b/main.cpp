#include <iostream>
#include <string>
#include <map>
#include <functional>

using namespace std;

class functor{
public:
    void operator()(int i){
        cout << i << endl;
    }
    void operator()(string s){
        cout << s << endl;
    }
    void operator()(int i, int j){
        cout << i+j << endl;
    }
};


int main(){
    // i know i should put something here thats not "functor" 
    // but i have no idea what. 
    map<int,std::function<void()>> hTable;

    // add elements into a table like this...
    hTable[0] = std::bind(functor(), 2);
    hTable[1] = std::bind(functor(), "foo and bar are overrated, boo.");
    hTable[2] = std::bind(functor(), 2, 3);

    // and fire the function in the table simply like this
    hTable[0]();

    cin.get();
    return 0;
}