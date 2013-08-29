#include <iostream>
#include <vector>
#include <functional>


#define ASSERT_TWO(a,b) static_assert((void*)#a != (void*) #b, #a  " and " #b " are same variables passed to ASSERT_TWO.") 


int *global;

int main()
{
    int *local;
    
    ASSERT_TWO(global, local);
    ASSERT_TWO(local, global);
    
    ASSERT_TWO(global, global);
    ASSERT_TWO(local, local);
    
    (void)local; //suppress unsused warning!
}