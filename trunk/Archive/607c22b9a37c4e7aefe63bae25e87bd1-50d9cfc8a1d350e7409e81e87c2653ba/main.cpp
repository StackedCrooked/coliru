/* 
* This is a program built by a team of students
* to help local movie theaters sell tickets
* 
* File: main.cpp
* Author(s):
*
* 
* Created on April 15, 2013, 11:10 AM
*/


#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <iomanip>


namespace A{

    template<class T,unsigned DIM>
    class CMyTable{
        public:
            int i;
            
        friend std::ostream& operator<<(std::ostream& s, const CMyTable<T,DIM>& vec) {
            s << vec.i;
        }
    };  

};




int main() {
    A::CMyTable<int,2> c;
    c.i = 3;
    
    std::cout << c;
}








