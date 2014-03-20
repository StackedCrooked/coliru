#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
 
using namespace std;
 
string test[] = {"one", "two", "three"};
string test2[] = {"a", "b", "c"};
 
class StaticTest {
    public:
    string nonStaticString1;
    vector <string> TEST1;
   
    string nonStaticString2;
    vector <string> TEST2;
   
    void set_values (vector <string> temporary1, vector <string> temporary2) {
        nonStaticString1 = "nonStaticString1";
        TEST1 = temporary1;
        nonStaticString2 = "nonStaticString2";
        TEST2 = temporary2;
    }
   
    void print_values (string nonStaticString, vector <string> values) {
                cout << "The " << nonStaticString << " are:\n\n";
                for (int i = 0; i < values.size(); i++) {
                cout << values[i] << endl;
                }
                cout << endl;
        }
   
    class insideClass {
        StaticTest& own;
        public:
        insideClass(StaticTest& own) : own(own) {}
        void Overview () {
            own.print_values (own.nonStaticString1, own.TEST1);
        }
    };
};
 
int main () {    
    srand (time(NULL));
        vector <string> a;
        a.assign (test, test + sizeof (test) / sizeof (test[0]));
   
    vector <string> b;
    b.assign (test2, test2 + sizeof (test2) / sizeof (test2[0]));
   
    StaticTest Trial1;
    Trial1.set_values (a,b);
   
    StaticTest::insideClass insideTrial1(Trial1);
    insideTrial1.Overview ();
}