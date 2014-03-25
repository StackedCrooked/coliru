#include <iostream>                                                                                                                  
#include <future>                                                                                                                    
                                                                                                                                     
using namespace std;                                                                                                                 
                                                                                                                                     
                                                                                                                                     
void say_something()                                                                                                                 
{                                                                                                                                    
        cout << "Hi! Whats up!" << endl;                                                                                             
}                                                                                                                                    
                                                                                                                                     
                                                                                                                                     
int main()                                                                                                                           
{                                                                                                                                    
        cout << "Hello, World!" << endl;                                                                                             
                                                                                                                                     
        async(say_something);                               
        
        for (auto i = 0; i <= 1000000000; i++);
                                                                                                                                     
        cout << "Good bye, World!" << endl;                                                                                             
}