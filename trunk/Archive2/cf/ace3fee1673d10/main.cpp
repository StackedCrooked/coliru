#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <cxxabi.h>

using namespace std;

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

struct Time    { };
struct Point2D { };
struct Drawing { };

template <typename T>
using Behavior = function <T (Time)>;

template <typename T>
Behavior<T> always (T val) 
{   return [val](Time) 
    {   return val;  };  }
    
template <typename R, typename A>
Behavior<R> map 
(   function<R(A)> r4a
,   Behavior<A> b   ) 
{   return [r4a, b] (Time t)
    {   return r4a (b (t));  };  }

template <typename R, typename A1, typename A2>
Behavior<R> map 
(   function<R(A1, A2)> r4as
,   Behavior<A1> b1
,   Behavior<A2> b2) 
{   return [b1, b2, r4as] (Time t)
    {   return r4as (b1 (t), b2 (t));  };  }

Point2D mousePos (Time t) { Point2D p; return p; }
Drawing circleAt (Point2D c) { Drawing d; return d; }

Behavior<Drawing> 
circleFollowsMouse (Behavior<Point2D> mousePos)
{   return map<Drawing, Point2D> (circleAt, mousePos);  }  

Drawing drawOver (Drawing top, Drawing bottom)
{   Drawing d; return d;  }
Behavior<Drawing> topBehavior = [] (Time) { Drawing d; return d; };
Behavior<Drawing> botBehavior = [] (Time) { Drawing d; return d; };
Behavior<Drawing> combined = 
    map<Drawing, Drawing, Drawing> (drawOver, topBehavior, botBehavior);

int main()
{   auto c = circleFollowsMouse (mousePos);
    cout << "c: " << type_name<decltype(c)>() << endl;
    Time t;
    auto r = c(t);
    cout << "c(t) : " << type_name<decltype(r)>() << endl;
    cout << "combined : " << type_name<decltype(combined)>() << endl;
    r = combined(t);
    cout << "combined(t) : " << type_name<decltype(r)>() << endl;
}
