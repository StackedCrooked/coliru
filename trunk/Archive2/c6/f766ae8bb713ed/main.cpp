#include <iostream>
#include <string>
#include <vector>

#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp> 

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


class B
{
public:

    typedef boost::function< int (int) >  CallBackFunction;
    template <typename FunctionParameter>
    int CallFunction(CallBackFunction pi_func,FunctionParameter  param)
    {
         std::cout<<"12432543555adsfdsgdfsgggggggggggggggg"<<std::endl;
		return pi_func(param);
	}
};

class A
{
    B b;
public:

  //void func(boost::tuple<int,int,std::string> a)
  int func(int a)
  {
      std::cout<<"adsfdsgdfsgggggggggggggggg"<<std::endl;
      return 0;
  }
  
  void test()
  {
        std::cout<<"test"<<std::endl;
      //b.CallFunction(boost::bind(&A::func,this,_1),boost::make_tuple(0,1,"aaa"));
      b.CallFunction(boost::bind(&A::func,this,_1),0);
  }
};





int main()
{
     std::cout<<"main"<<std::endl;
    //A a;
    //a.test();
}
