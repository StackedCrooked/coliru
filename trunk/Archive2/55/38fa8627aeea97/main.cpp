#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <ctime>
#include <boost/algorithm/string.hpp>

using namespace std;

void tslinstatictest();

void printarray (int arg[], int length) {
  int *p=arg[];
  int len=sizeof(p)/sizeof(*p);
  if (length>len) { break; }
  for (int n=0; n<length; ++n)
    cout << arg[n] << ' ';
  cout << '\n';
}

class Foo
{
        public:
        Foo( int x ) 
        {
                std::cout << "Foo's constructor " 
                          << "called with " 
                          << x 
                          << std::endl; 
        }
};

class Bar : public Foo
{
        public:
        Bar()  : Foo(0x9f) // construct the Foo part of Bar
        { 
                std::cout << "Bar's constructor" << std::endl; 
        }
        
        double value() { return 1118; }
};

class Tslin : public Foo , public Bar
{
    public:
    Tslin() : Foo(88), Bar()
    {
            std::cout<<"Tsssss"<<std::endl;
    }
};

namespace foo
{
  int value() { return 5; }
}

namespace bar
{
  const double pi = 3.1416;
  double value() { return 2*pi; }
}

int main() {
    
    string str="Tslin-- yyy";
    string *p=&str;
    
    //reverse(str.begin(), str.end()); 
    reverse(p->begin(), p->end());
    
    cout<<str<<endl;
    cout<<*p<<endl;
    
    for(int i=0;i<10;i++){
        tslinstatictest();
    }
    cout<<endl;
    
    reverse(p->begin(), p->end());
    
    string str2=*p;
    
    cout<<"str2="<<str2<<endl;
    
    if(boost::iequals(str,str2)){
        cout<<"same"<<endl;
    } else {
        cout<<"different"<<endl;
    }
    
    srand(time(NULL));
    
    /*float LO=2,HI=5,Z=3;
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    cout<<"r="<<r<<endl;
    float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/Z));
    cout<<"r2="<<r2<<endl;
    float r3 = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
    cout<<"r3="<<r3<<endl;*/
    
    string str5 = "77";
    char * ptr;
    long ntr = strtol( str5.c_str(), & ptr, 8 );
    if ( * ptr != 0 ) {
        cout << "not a number" << endl;
    }
    else {
        cout << ntr << endl;
    }
    
    //Bar bar;
    cout<<bar::value()<<endl;
    //cout<<bar.value()<<endl;
    
    Tslin tslin;
    
    int tsarray[] = {81,87,83};
    printarray(tsarray,4);

    return 0;
    
}

void tslinstatictest(){
    static int x=1;
    cout<<x<<" ";
    x+=1;
}