#include <iostream>
using namespace std;

class test{
    int *ptr;

public:

    test(const test&) = delete;

    test(int t=0){

        ptr=new int;
        *ptr=t;
    }

    void increment(){

    (*ptr)++;
    }

    void display(){
        cout<<*ptr<<endl;

    }


    };

    int main(){


 test t1;

t1.display();
t1.increment();
t1.display();

test t2(t1);//copy constructor
t2.display();

t1.increment();

t1.display();   
t2.display();
    }