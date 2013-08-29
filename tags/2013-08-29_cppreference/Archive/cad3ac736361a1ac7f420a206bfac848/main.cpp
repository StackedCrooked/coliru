#include <boost/utility/typed_in_place_factory.hpp>
#include <boost/optional.hpp>

class A {};
void do_something(const A&, const A&) {}

int main() {
    boost::optional<A> a1; //a1 is an object that might be an A or nothing
    boost::optional<A> a2; //a1 is an object that might be an A or nothing
    try {
        a1 = boost::in_place<A>(); //in this place, make an A
        a2 = boost::in_place<A>(); //in this place, make an A
    } catch(...) {
        if (a1) {
            //if a1 exists then a2 threw
        } else {
            //otherwise a1 threw
        }
    }
    do_something(*a1, *a2);
}