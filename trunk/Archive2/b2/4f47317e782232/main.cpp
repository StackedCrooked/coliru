#include <deque>
#include <vector>
#include <iostream>

class A {
public:
    
    A() = default;
    A(const A&) {
        ++numCopies;
    }

    A& operator=(const A&) {
        ++numCopies;
        return *this;
    }

    A(A&&) {
        ++numMoves;
    }

   A& operator=(A&&) {
        ++numMoves;
        return *this;
    }

    static int numCopies;
    static int numMoves;
};

int A::numCopies = 0;
int A::numMoves = 0;

int main()
{
    std::deque<A> d(10000);
    d.erase(d.begin() + 5000);
    std::cout << A::numCopies << ' ' << A::numMoves << std::endl;  
}