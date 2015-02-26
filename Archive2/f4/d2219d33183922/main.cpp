#include <iostream>


struct Item { };


int main()
{   
    Item item();
    item(); // call it    
}


// function implementation
Item item() { return {}; }
