//http://stackoverflow.com/questions/28184984/different-behavior-of-c11-list-initialization
#include <string>
#include <iostream>

#define PRINT 0
#define NESTED 1

class A {
private:
  std::string s;
public:
  A() = delete;
  A(const A&) = delete;
  A(A&&) = delete;
  A(const std::string &a) : s(a) {}
#if PRINT
  friend std::ostream & operator<<( std::ostream & o, const A& x ) { return o << x.s; }
#endif
};

class Aggr {
private:
#if NESTED
    struct {
        A arr[2];
    }aggregate;
#else
    A aggregate[2];
#endif
public:
    Aggr() : aggregate{
#if NESTED
        {
#endif
            {"[0]"} // Copy initialize [0]
            ,
            {"[1]"} // Copy initialize [1]
#if NESTED
        }
#endif
    } {}
#if PRINT
    friend std::ostream & operator<<( std::ostream & o, const Aggr& x ) {
        return o
#if NESTED
            << x.aggregate.arr[0] << std::endl
            << x.aggregate.arr[1] << std::endl
#else
            << x.aggregate[0] << std::endl
            << x.aggregate[0] << std::endl
#endif
        ;
    }
#endif
};

int main() {
    Aggr obj;
#if PRINT
    std::cout << obj << std::endl;
#endif
}

