#include <iostream>
#include <boost/mpl/list.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/distance.hpp>

struct First{};
struct Second{};
struct Third{};

typedef boost::mpl::list<First, Second, Third> types;
unsigned int indexes[] = {1, 2, 3};

template <typename T>
unsigned int index(const T&){
    typedef typename boost::mpl::begin<types>::type first;
    typedef typename boost::mpl::find_if<types, boost::mpl::same_as<T> >::type iter;
    return indexes[boost::mpl::distance<first, iter>::value];
}

int main()
{
    using namespace std;
    
    cout << index(First()) << " " << index(Second()) << " " << index(Third()) << endl;

}
