//http://stackoverflow.com/questions/28184984/different-behavior-of-c11-list-initialization
#include <string>
#include <iostream>

// Problem seems to be the nested braces, g++ sees braces and says this isn't a scalar type
// so it doesn't try to implicitly construct a string from a const char*
// clang goes one level deeper, sees the const char*, invokes the string ctor, now has compatible type
#if 0
What does the standard say ?

8.5.1/2 : When an aggregate is initialized by an initializer list, as specified in 8.5.4,
          the elements of the initializer list are taken as initializers for the members of the aggregate,
          in increasing subscript or member order.
          Each member is copy-initialized from the corresponding initializer-clause.
          
It is explained that:

8.5/14 : (...) is called copy-initialization. [ Note: Copy-initialization may invoke a move (12.8). —end note ]
But I found no evidence in 12.8 that in your specific case a move would be required.

8.5.4/3 Otherwise, if T is a class type, constructors are considered.
        If T has an initializer-list constructor, the argument list consists of
        the initializer list as a single argument;
        otherwise, the argument list consists of the elements of the initializer list.
        The applicable constructors are enumerated and the best one is chosen through
        overload resolution (13.3).

#endif

template<typename T>
class A {
private:
  T s;
public:
  A() = delete;
  A(const A&) = delete;
  A(A&&) = delete;
  A(const T &a) : s(a) {}
  friend std::ostream & operator<<( std::ostream & o, const A& x ) { return o << x.s; }
};

#define ARRAY 1
class Aggr {
private:
#if ARRAY
    struct {
        A<std::string> arr[2];
    }aggregate;
#else
    struct {
        std::string m_a;
        const char* m_b;
        A<std::string> m_c;
        A<const char*> m_d;
        std::string m_e[1];
        const char* m_f[1];
        const char* m_g[2];
        std::string m_h[2];
        A<std::string> m_i[2];
        A<const char*> m_j[2];
    } aggregate;
#endif
public:
    Aggr() : aggregate{
#if ARRAY
        {
            {"i[0]"} // Copy initialize member m_i[0]
            ,
            {"i[1]"} // Copy initialize member m_i[1]
        }
#else
        {"a"} // Copy initialize member m_a
        ,
        "b"   // Copy initialize member m_b
        ,
        {"c"} // Copy initialize member m_c
        ,
        {"d"} // Copy initialize member m_d
        ,
        {"e"} // Copy initialize member m_e
        ,
        {"f"} // Copy initialize member m_f
        ,
        {
            "g[0]" // Copy initialize member m_g[0]       // with braces gets error braces around scalar initializer for type 'const char*'
            ,
            "g[1]" // Copy initialize member m_g[1]
        }
        ,
        {
            "h[0]" // Copy initialize member m_h[0]       // works with or without braces
            ,
            "h[1]" // Copy initialize member m_h[1]
        }
        ,
        {
            {"i[0]"} // Copy initialize member m_i[0]     // remove braces and get cannot convert
            ,
            {"i[1]"} // Copy initialize member m_i[1]
        }
        ,
        {
            {"j[0]"} // Copy initialize member m_j[0]     // remove braces and get deleted move ctor
            ,
            {"j[1]"} // Copy initialize member m_j[1]
        }
#endif
    } {}
    friend std::ostream & operator<<( std::ostream & o, const Aggr& x ) {
        return o
#if ARRAY
            << x.aggregate.arr[0] << std::endl
            << x.aggregate.arr[1] << std::endl
#else
            << x.aggregate.m_a << std::endl
            << x.aggregate.m_b << std::endl
            << x.aggregate.m_c << std::endl
            << x.aggregate.m_d << std::endl
            << x.aggregate.m_e[0] << std::endl
            << x.aggregate.m_f[0] << std::endl
            << x.aggregate.m_g[0] << std::endl
            << x.aggregate.m_g[1] << std::endl
            << x.aggregate.m_h[0] << std::endl
            << x.aggregate.m_h[1] << std::endl
            << x.aggregate.m_i[0] << std::endl
            << x.aggregate.m_i[1] << std::endl
            << x.aggregate.m_j[0] << std::endl
            << x.aggregate.m_j[1] << std::endl
#endif
        ;
    }
};

int main() {
    Aggr obj;
    std::cout << obj << std::endl;
}

