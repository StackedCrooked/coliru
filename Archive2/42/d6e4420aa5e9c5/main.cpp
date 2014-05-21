#include <stack>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

double parse(std::string input) 
{
    stack<string> ops;
    stack<double> vals;
    getline(cin, input);
    istringstream scanner(input);
    while(true){
        double num;
        scanner >> num;
        if(scanner.fail() && scanner.eof())     break;
        else if(!scanner.fail())                vals.push(num);
        else{
            scanner.clear();
            string token;
            scanner >> token;
            if(token == "(")                    ;
            else if(token == "+")               ops.push(token);
            else if(token == "*")               ops.push(token);
            /*Add more operations here (Log, sin, cos...)*/
            else if(token == ")"){
                string op = ops.top();
                ops.pop();
                if(op == "+"){
                    double a, b;
                    a = vals.top();
                    vals.pop();
                    b = vals.top();
                    vals.pop();
                    vals.push(a+b);
                }
                else if(op == "*"){
                    double a, b;
                    a = vals.top();
                    vals.pop();
                    b = vals.top();
                    vals.pop();
                    vals.push(a*b);
                }
                /*Add more operations here*/
            }
        }
    return vals.top();
    }
    return -1;
}

int main() {
    std::cout << parse("( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )");
}