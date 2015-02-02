#include <deque>
#include <vector>
#include <iostream>

class A {
public:
    
    A() = default;
    A(const A&) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        ++numCopies;
    }

    A& operator=(const A&) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        ++numCopies;
        return *this;
    }

//  Uncomment the following lines to see the behavior with move operations enabled.
//    A(A&&) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
//        ++numMoves;
//    }
//
//    A& operator=(A&&) {
//        std::cout << __PRETTY_FUNCTION__ << std::endl;
//        ++numMoves;
//        return *this;
//    }

    static int numCopies;
    static int numMoves;
};

int A::numCopies = 0;
int A::numMoves = 0;

int main()
{
    std::deque<A> d(10);
    d.erase(d.begin() + 5);
    std::cout << "Deque stats: " << A::numCopies << " copies, " << A::numMoves << " moves." << std::endl;  

    A::numCopies = 0;
    A::numMoves = 0;

    std::vector<A> v(10);
    v.erase(v.begin() + 5);
    std::cout << "Vector stats: " << A::numCopies << " copies, " << A::numMoves << " moves." << std::endl;  
}