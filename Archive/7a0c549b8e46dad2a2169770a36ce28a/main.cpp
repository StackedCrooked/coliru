#include <iostream>
#include <vector>
#include <functional>


#define ASSERT_TWO(a,b) static_assert((void*)#a != (void*) #b, "'" #a  "' and '" #b "' are same variables passed to ASSERT_TWO.") 


int *global;

int main()
{
    int *local;
    
    ASSERT_TWO(global, local);  //should pass
    ASSERT_TWO(local, global);  //should pass
    
    ASSERT_TWO(global, global); //should fail
    ASSERT_TWO(local, local);   //should fail
    
    (void)local; //suppress unsused warning!
}