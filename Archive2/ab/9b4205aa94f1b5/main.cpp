#include <iostream>
#include <string>
#include <vector>
#include <array>


struct ReturnRealOne{ //struct because its implicit public
   static int someFunctionReturning(){ //this is the implementation of the real function(s)
        return 1;
    }
};

struct ReturnFakeTwo{
   static int someFunctionReturning(){ //this is some fake implementation
        return 2;   
        
    }
};

/*
This function returns the real or the fake one depending on the template class
*/
template <class T>
int someFunctionIWantToTestUT(){ 
   return  T::someFunctionReturning();
}

typedef int (*someFunctionIWantToTestFP)(); //function pointer definition, between ( and ) you can add parameters -> see function pointers
someFunctionIWantToTestFP someFunctionIWantToTest = someFunctionIWantToTestUT<ReturnRealOne>; //The one function pointer pointing to the real one
someFunctionIWantToTestFP fakeSomeFunctionIWantToTest = someFunctionIWantToTestUT<ReturnFakeTwo>; // The one function pointer pointing to the fake one


int main()
{
std::cout << someFunctionIWantToTest() << std::endl;  
std::cout << fakeSomeFunctionIWantToTest() << std::endl;
}
