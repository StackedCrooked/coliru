template<class input_type, class func_type>
auto rfor_each(input_type&& type, func_type&& func, int) ->decltype(func(type)) { return func(type);}
template<class input_type, class func_type>
void rfor_each(input_type&& type, func_type&& func, ...) { for(auto&& i : type) rfor_each(i, func, 0);}

#include <iostream>
int main()
 {

     std::cout << std::endl;
     double B[3][3] = { { 1.2 } };
     rfor_each(B[1], [](double&v){v = 5;});
     auto func = [](double (&i)[3]) {std::cout << "{"; for(double d:i) std::cout << d << ", "; std::cout << "}\n";};
     rfor_each(B, func);
     // 1, 0, 0, 0, 0, 0, 0, 0, 0,
 };