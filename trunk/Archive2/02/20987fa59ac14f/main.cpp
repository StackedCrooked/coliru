#include <iostream>
using namespace std;

int ob=0;//counts how many objects are created via overloaded new
void* operator new(size_t size, string st) 
{
    cout<<st<<endl;
    cout<<"this is overloaded version of new, new allocates "<<size<<endl;
    ob++;
    return malloc(size); 
 }
 void operator delete(void * ptr) noexcept
 {
    free((void*)ptr);
    ob--;
    cout<<"end of destruction"<<endl;
 }
 int main()
 {
    int* ptr = new (5, "hello world") int;
    cout<<*ptr<<endl;
    cout<<ob<<" objects exist"<<endl;
    delete(ptr);
    cout<<ob<<" objects exist"<<endl;
    return 0;
 }