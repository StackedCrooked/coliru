#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <cstdlib>
using std::srand;
using std::rand;

int main() 
{
    srand ( std::time ( 0 ) ); // use current time as seed for random generator
    int random_variable = rand ();
    
    
    cout << "Random value between 0 - 99 :";
    cout << random_variable % ( 99 - 0 + 1 ) + 0 << std::endl;
    
    cout << "Random value between 15 - 99 :";
    cout << random_variable % ( 99 -15 + 1 ) + 15 << std::endl;
   
}