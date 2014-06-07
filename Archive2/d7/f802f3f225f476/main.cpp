#include <utility>

struct Nil {}; 

template<class HEAD, class REST> struct Cons;
template<class HEAD, class REST>
struct Cons : public REST {
    typedef HEAD curtype;
};
template<class HEAD>
struct Cons<HEAD,Nil> {};

template<class HEAD, class REST>
Cons<HEAD,REST> operator+(Cons<HEAD,REST>) 
{return {};}

template<class HEAD, class REST, class TAIL>
auto operator+(Cons<HEAD,REST>, Cons<TAIL,Nil> r) 
-> Cons<HEAD,decltype(std::declval<REST>()+r)>
{return {};}

template<class HEAD, class TAIL>
Cons<HEAD,Cons<TAIL,Nil>> operator+(Cons<HEAD,Nil>, Cons<TAIL,Nil>) 
{return {};}

#define START_LIST(NAME) using NAME = decltype(
#define ADD_TO_LIST(NAME,TYPE) + std::declval<Cons<TYPE,Nil>>()
#define END_LIST(NAME) );


START_LIST(List)
ADD_TO_LIST(List, int)
ADD_TO_LIST(List, float)
ADD_TO_LIST(List, double)
END_LIST(List)

int main() {
    List l;
}