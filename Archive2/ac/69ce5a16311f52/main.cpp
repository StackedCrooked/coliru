#include <iostream>           // std::cout
#include <vector>
#include <thread>
#include <new>
#include <algorithm>

using namespace std;

int len = 9999999;

void foo(char* b) {
    b = new char[len];
    std::fill(b, b+len, '\0');   
}

int main ()
{
    char* b;
//    b = new char[len];
//    std::fill(b, b+len, '\0');   
    vector<thread> vec;
    
    for (int i = 0; i < 40; ++i) 
        vec.push_back(thread(foo, b);
        
    for(auto& thread : vec) 
        thread.join();



  return 0;
}






















