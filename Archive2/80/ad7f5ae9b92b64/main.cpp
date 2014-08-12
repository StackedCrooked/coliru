#include <boost/shared_ptr.hpp>

int main () {
    boost::shared_ptr<const int> p ( new int);
    (*p)++;
}