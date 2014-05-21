
template<class T>
struct TypeMap {
};

#include <string>

template<class T0, class T1, class T2>
std::string at(const TypeMap<std::string>&,
               typename std::enable_if<std::is_convertible<T0,int>::value,int*>::type=0,
               typename std::enable_if<std::is_convertible<T1,double>::value,double*>::type=0,
               typename std::enable_if<std::is_convertible<T2,char>::value,char*>::type=0
               )
{return "Hey";}


#include <iostream>
int main() {
    TypeMap<std::string> MyMap;
    std::cout << at<int,float,char>(MyMap);
}
