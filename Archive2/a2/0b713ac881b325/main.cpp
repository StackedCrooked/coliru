#include <iostream>
using namespace std;
void change(int &val){
val=20;
}
int main() {
int x=10;
change(x);
cout<<x;
/*string *str=0;
string *str1=new string("hello");
string *dat=0;
//delete str;
str=dat;*/


/*string *s=new string("hello");
string *ptr=s;
//
//delete s;
delete ptr;*/
string str("hello");;
string *ptr=&str;
delete ptr;
    return 0;
}