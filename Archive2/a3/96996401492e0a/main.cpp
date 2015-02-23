#include <iostream>
#include <string>
#include <vector>
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

#include <typeinfo>
#include <iostream>
//class template
template<typename T1, typename T2, int para>
class MClass
{
public:
    int length=para;
    T1 m_a;
    T2 m_b;
    void id();
   
};

template<typename T1, typename T2, int para>
void MClass<T1, T2, para>::id() {
        std::cout<<"I am template<typename T1, typename T2, int para> class\n";
    }

//function template
template <typename T1, class T2, int para>
void mf(T1 a, T2 b, double x)
{
    std::cout<<"T1 is of type "<<typeid(T1).name()<<" and has value "<<  a <<"\n";
    std::cout<<"T2  is of type "<<typeid(T2).name()<<" and has value "<<  b <<"\n";
    std::cout<<"parameter has value "<< para <<"\n";
      std::cout<<" x is normal parameter and has value "<< x <<"\n";
    }

template <typename A>
class MC{
    
    void print(){
        
    std::cout<<"O\n";
        }
    };
    
template <>
void MC<int>::print(){
    std::cout<<"XXX\n";
    }

int main(){
using mO= MC mymc<double >;
//mymc<double >.print();
return 0;
}