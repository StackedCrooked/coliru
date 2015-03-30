#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void foo(initializer_list<int> x)
{
    //static_assert(x.size()==2, "dd"); // decomment for bestemmie
    int arr[x.size()];
     arr[0] = 10;
    cout << arr[0] << endl;
}


int main(int argc, char *argv[])
{  
   foo({1,2});    
}


