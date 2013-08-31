#include <iostream>

template <class T>
struct Data1{
  T d1;   
}; 

template <class T>
struct Data2{
  T d1,d2;   
}; 

template<class T>
struct D1{ Data1<T> xx; };

template<class T>
struct D2{ Data2<T> xx; };

template<class T>
struct traits { };

template<>
struct traits<D1<double>> {
    typedef D1<double> type;
    typedef Data1<double>  xD;
    typedef Data1<double>*  pxD; 
};
    
template<>
struct traits<D1<float>> {
    typedef D1<float> type;
    typedef Data1<float>  xD;
    typedef Data1<float>*  pxD;  
};
    
template<>
struct traits<D2<double>> {
    typedef D2<double> type;
    typedef Data2<double>  xD;
    typedef Data2<double>* pxD; 
};
    
template<>
struct traits<D2<float>> {
    typedef D2<float> type;
    typedef Data2<float>  xD;
    typedef Data2<float>*  pxD; 
};

template<class T>
void func2(Data1<T>* p_data1){
     // some computation here
}

template<class T1, class T2>
void funct1(){
  typedef typename traits<T2>::pxD  pxD;
  pxD yyy;
  func2(yyy);
}

int main(){

  funct1<double,D1<double>>();
  return 0;
}
