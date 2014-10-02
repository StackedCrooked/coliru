#include <iostream>

struct SpecializingType{};

template<typename T> 
struct Element
{   
   Element(std::string i)
   {
       message = "generic int";
   }    

   Element(float i)
   {
       message = "generic float";
   }   


std::string message;
}; 

template<> Element<SpecializingType>::Element(float i){message = "float specialized";}


int main()
{
    Element<SpecializingType> element_int(0.0);
    std::cout << element_int.message << std::endl;
    
    Element<float> element_float(0.0);
    std::cout << element_float.message  << std::endl;
    
}