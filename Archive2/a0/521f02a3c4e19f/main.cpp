#include <iostream>
#include <string>
#include <vector>
struct z{
    int x;
// virtual  ~z(){}
    };
struct t{
    z y;
    int x;
   t(){}
  t(t&&a)=delete;
 //t()=default;
   // t(std::initializer_list<int> a){
   t(int k){std::cout<<"123"<<std::endl;}
 //   t(std::initialer_list<int> k){}
    };
int main(){
    t a[2]{1};
    std::cout<<a[1].x<<" "<<a[1].y.x<<std::endl;
}