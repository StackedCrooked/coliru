#include <iostream>
#include <vector>
#include <array>

int main()
{
    std::vector<int> vec; //Ich bin ein dynamisches array vom datentyp int
    std::array<int, 50> arr; //Ich bin ein stinknormales langweiliges array vom datenyp int und kann max 50 elemente abspeichern
    
    //fill vector with 50 elements;
    for(auto i = 0; i < 50; ++i)
        vec.push_back(i); //push_back vergroessert den vector um 1 und platziert den neuen wert hinten dran
        
    //fill array
    for(unsigned int  i = 0; i < arr.max_size(); ++i) //hier max_size weil das array noch leer ist und somit arr.size() 0 ist
        arr[i] = i;
        
    // vector ausgeben
    for(auto elem : vec) // das selbe wie: for(int i=0; i < vec.size(); ++i) { int elem = vec[i]; ...
        std::cout << elem << " ";
        
    std::cout << std::endl;
    
    //array ausgeben;
    for(unsigned int i = 0; i < arr.size(); ++i) //wir haben ja das array befuellt, also koennen wir arr.size() verwenden;   warum hier kein for(auto elem : arr)  weil ich programmieren kann wie ich will!
        std::cout << arr[i] << " " ;
        
    std::cout << std::endl;
    
    //return ist nicht notwendig :P
}
