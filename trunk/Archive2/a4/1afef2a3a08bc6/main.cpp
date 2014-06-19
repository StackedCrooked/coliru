#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <cxxabi.h>

using namespace std;
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

template <class T> std::string
type_name()
{   typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void(*)(void*)> own
        (
            abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                nullptr, nullptr),
            std::free
            );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

typedef double Time;
struct Point2D { };
struct Drawing { };

template <typename T>
using Behavior = function <T (Time)>;

template <typename T>
Behavior<T> always (T v) 
{   return [v](Time) 
    {   return v;  };  }
    
template <typename R, typename A>
Behavior<R> map 
(   function <R (A)> r4a
,   Behavior<A> b   ) 
{   return [r4a, b] (Time t)
    {   r4a (b (t));  };  }

/** /
template <typename R, typename A1, typename A2>
Behavior<R> map 
(   function <R (A1, A2)> r4as
,   Behavior<A1> b1
,   Behavior<A2> b2) 
{   return [b1, b2, r4as] (Time t)
    {   r4as (b1 (t), b2 (t));  };  }
/**/

Point2D mousePos (Time t) { Point2D p; return p; }
Drawing circleAt (Point2D c) { Drawing d; return d; }

Behavior <Drawing> 
circleFollowsMouse (Behavior <Point2D> mousePos)
{   cout << type_name<decltype (mousePos)>() << endl;
    cout << type_name<decltype (circleAt)>() << endl;
    auto weird = (function<Drawing(Point2D)>(circleAt));
    cout << type_name<decltype ((function<Drawing(Point2D)>(circleAt)))>() << endl;
    auto result = [mousePos] (Time t) {   return circleAt (mousePos (t));  };
    cout << "result: " << type_name<decltype (result)>() << endl;
    auto result2 = [weird, mousePos] (Time t) {   return weird (mousePos (t));  };
    cout << "result2: " << type_name<decltype (result2)>() << endl;
    
    return [mousePos] (Time t) { return circleAt (mousePos (t));  };  }
//    return map (circleAt, mousePos);  }
  

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    auto c = circleFollowsMouse (mousePos)(42);
    cout << "c: " << type_name<decltype(c)>() << endl;

}
