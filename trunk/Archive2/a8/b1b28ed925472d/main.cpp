#include <iostream>
#include <ctime>
#include <boost/container/vector.hpp>
#include <boost/container/list.hpp>
using namespace std;

#define NUM_ITER 100000

int main() {
    clock_t t = clock();
    boost::container::list< int > my_list;
    boost::container::vector< boost::container::list< int >::iterator > list_ptr;

    list_ptr.reserve(NUM_ITER);

    for(int i = 0; i < NUM_ITER; ++i) {
        my_list.push_back(rand());
        list_ptr.push_back(--(my_list.end()));
    }

    unsigned long long volatile accum = 0;

    while(my_list.size() > 0) {
        accum += *list_ptr[list_ptr.size()-1];
        my_list.erase(list_ptr[list_ptr.size()-1]);
        list_ptr.pop_back();
    }

    cout << "Done in: " << 1000*(clock()-t)/CLOCKS_PER_SEC << " msec!" << endl;
    cout << "Accumulated: " << accum << "\n";
}
