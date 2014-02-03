#include <iostream>


using std::cout ; using std::cin; using std::endl;






template <int first,int...Args> struct sigma  {

 constexpr static int result = first + sigma<Args...>::result   ;
};



template<>  struct sigma <int tmp> {

 constexpr static int result = tmp ;
};

int main(int argc, char** argv){

  
  
  cout << sigma<1,2,3,4,5,0>::result << endl; 
  

  return 0 ; 


}