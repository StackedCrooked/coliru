#include <future>
#include <list>
#include <iostream>
#include <exception>
using namespace std;

void task1()
{
   // endless insertion and memory allocation
   // - will sooner or later raise an exception
   // - BEWARE: this is bad practice
   list<int> v;
   while (true) {
       for (int i=0; i<1000000; ++i) {
           v.push_back(i);
       }
       cout.put('.').flush();
        throw 1;;
   }
}

int main()
{
   cout << "starting 2 tasks" << endl;
   cout << "- task1: process endless loop of memory consumption" << endl;
   cout << "- task2: wait for <return> and then for task1" << endl;

   auto f1 = async(task1);  // start task1() asynchronously (now or later or never)

   cout << "\nwait for the end of task1: " << endl;
   try {
       f1.get();  // wait for task1() to finish (raises exception if any)
   }
   catch (const exception& e) {
       cerr << "EXCEPTION: " << e.what() << endl;
   }
   catch (...) {
       cerr << "EXCEPTION: " <<  endl;
   }
}