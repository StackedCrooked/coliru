
#include <cstdlib>
#include <ctime>
#include <algorithm>    // std::copy    
#include <iostream>

using namespace std;


int main(){
    const int n=5;
    int a[n],c[n];
    for(int j=0;j<n;j++) a[j]=j;
    std::copy(a+1,a+n,c);
    for (int i=0;i<n-1;++i){
      for(unsigned int j=0;j<n-1;j++)   std::cout << c[j] << std::endl;
      std::cout << "aaa" << std::endl;
      c[n-1]=a[i];
      swap(c[i],c[n-1]);
    }
    
    vector<int> b(a+1,a+n); 
    for (int i=0;i<n-1;++i){
      for(unsigned int j=0;j<b.size();j++)   std::cout << b[j] << std::endl;
      std::cout << "baa" << std::endl;
      b.push_back(a[i]);
      swap(b[i], b[b.size()-1]);
      b.pop_back();
    }
}
