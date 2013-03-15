struct A {
    static const char* myList[];    
};
const char* A::myList[] = {"item1","item2"};    

#include <iostream>
int main() {
    std::cout << A::myList[0];
}