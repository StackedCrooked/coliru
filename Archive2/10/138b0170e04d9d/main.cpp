template<class input_type, class func_type>
auto rfor_each(input_type&& input, func_type&& func, int) ->decltype(func(input)) 
{ return func(input);}

template<class input_type, class func_type>
void rfor_each(input_type&& input, func_type&& func, ...) 
{ for(auto&& i : input) rfor_each(i, func, 0);}

#include <iostream>
int main()
 {

     std::cout << std::endl;
     double B[3][3] = { { 1.2 } };
     rfor_each(B[1], [](double&v){v = 5;}); //iterate over doubles
     auto write = [](double (&i)[3]) //iterate over rows
         {
             std::cout << "{";
             for(double d : i) 
                 std::cout << d << ", ";
             std::cout << "}\n";
         };
     rfor_each(B, write );
 };