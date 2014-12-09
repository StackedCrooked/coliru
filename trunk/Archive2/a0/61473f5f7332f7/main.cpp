#include <stack>
#include <vector>
#include <functional>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    string x = "hey";
    stack<reference_wrapper<string>> obj_stack;
    obj_stack.push(x);
    string t = obj_stack.top().get();
    cout << t;
                         
}   
