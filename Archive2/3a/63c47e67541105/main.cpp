template<class input_type, class func_type>
auto rfor_each(input_type&& type, func_type&& func, int) ->decltype(func(type)) { return func(type);}
template<class input_type, class func_type>
void rfor_each(input_type&& type, func_type&& func, ...) { for(auto&& i : type) rfor_each(i, func, 0);}

#include <iostream>
int main()
 {
     using namespace std;
     int A[3][3][3] = {};
     rfor_each(A[1], [](int&v){v = 5;});
     rfor_each(A, [](int&v){std::cout << v << ", ";});

     std::cout << std::endl;
     double B[3][3] = { { 1.2 } };
     rfor_each(B, [](double i){ std::cout << i << ", "; });
     // 1, 0, 0, 0, 0, 0, 0, 0, 0,
 };