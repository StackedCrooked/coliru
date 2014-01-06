#include <iostream>
using namespace std;

struct foo{
    string *question;
    //other elements
};

int main(){
    foo *q;
    foo *q2;
    q->question = new string("This is a question"); 
    q2->question = new string("another question");
}