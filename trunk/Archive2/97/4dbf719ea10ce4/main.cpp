#include <iostream>
#include <string>
#include <vector>

using namespace std;

void log(string message) {
    cout<<message<<endl;
}

struct MyClass {
    
    string name;
    
    MyClass() {
        log("MyClass()");
    }
    
    ~MyClass() {
        log("~MyClass()");
    }
    
 
};

int main() {
    
    vector<MyClass> v;
    v.push_back(MyClass());

}