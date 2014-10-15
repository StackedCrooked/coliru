#include <list>
#include <vector>
#include <algorithm>
using namespace std;

// not necessary if ranges get into standard
template <typename T>
void sort(T&& container)
{
    std::sort(container.begin(), container.end());
}

template <typename T>
void do_sort_and_stuff(T container)
{
    container.sort();
    //sort(container);
    // other stuff
}

int main()
{
   list<int> l;
   vector<int> v;
   
   do_sort_and_stuff(l);
   do_sort_and_stuff(v);
}
