#include <iostream>
#include <string>
#include <vector>
#include <array>


struct ReturnRealOne{ //struct because its implicit public
   static int32_t someFunctionReturning(){ //this is the implementation of the real function(s), to be added to REAL code
        return 1;
    }
};

struct ReturnFakeTwo{
   static int32_t someFunctionReturning(){ //this is some fake implementation, to be added to TEST code only
        return 2;   
        
    }
};

/*
This function returns the real or the fake one depending on the template class
*/
template <class T>
int32_t someFunctionIWantToTestUT(){ 
   return  T::someFunctionReturning();
}

typedef int32_t (*someFunctionIWantToTestFP)(); //function pointer definition, between ( and ) you can add parameters -> see function pointers
someFunctionIWantToTestFP someFunctionIWantToTest = someFunctionIWantToTestUT<ReturnRealOne>; //The one function pointer pointing to the real one
someFunctionIWantToTestFP fakeSomeFunctionIWantToTest = someFunctionIWantToTestUT<ReturnFakeTwo>; // The one function pointer pointing to the fake one


int main()
{
std::cout << someFunctionIWantToTest() << std::endl;  
std::cout << fakeSomeFunctionIWantToTest() << std::endl;
}
