#include <iostream>
#include <string>

struct Bunny
{
    Bunny( std::string name ) { id = name ; std::cout << id << " constructor\n" ; }
    ~Bunny() { std::cout << id << " destructor\n" ; }
    
    std::string id ;
};

int main()
{
    Bunny* bugs_bunny = new Bunny( "Bugs Bunny" ) ; 
    // step 1. aquire memory from the frfee store for a Bunny object
    // step 2. construct the bunny object
    
    {
        Bunny miyamoto( "Miyamoto Usagi" ) ; 
        // step 1. appropriate memory from the frame of the function (usually stack) for a Bunny object
        // step 2. construct the bunny object
        
        // miyamoto is alive now
        
    }// the life-time of miyamoto is over now.
    // step 1. destroy the bunny object
    // step 2. return memory occupied by the Bunny object back to the frame (stack)
    
    
    delete bugs_bunny ;
    // step 1. destroy the bunny object
    // step 2. release memory occupied by the Bunny object
}
