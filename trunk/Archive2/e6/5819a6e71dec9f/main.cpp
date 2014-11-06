#include <iostream>
#include <memory> //declarations of unique_ptr 
#include <cstdlib>
using std::unique_ptr;
using namespace std;
int main()
{
  // default construction
    unique_ptr<int> up; //creates an empty object
      // initialize with an argument
    unique_ptr<int> uptr (new int(3));
    double *pd= new double;
    unique_ptr<double> uptr2 (pd);
      // overloaded * and ->
    *uptr2 = 23.5;
    unique_ptr<std::string> ups (new std::string("hello"));
    int len=ups->size();
  // cout << ups  << endl; 
  uptr2.reset(new double); //delete pd and acquire a new pointer
  uptr2.reset(); //delete the pointer acquired by the previous reset() call
unique_ptr<double, std::free> up1 ((double*)malloc(sizeof(double));
unique_ptr<double> up2;
up2.swap(up1);
*up2=3.45;

char* pp=(char*)malloc(10*sizeof(char));
unique_ptr<pp, decltype(free)*> intptr; //initialized with a custom deleter
*intptr=5;
}