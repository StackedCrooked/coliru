#include <iostream>
long factorial(int n)
      {if(n==0) return 1;
       else return factorial(n-1)*n;}
 
  int main()
        {int x;
            std::cout<<"x=";std::cin>>x;
            std::cout<<factorial(x) ;
            }