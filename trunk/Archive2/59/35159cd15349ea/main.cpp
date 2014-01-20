#include <boost/thread/locks.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include <vector>
#include <mutex>

int main()
{
    using mutex_list = std::vector<std::mutex*>;
    mutex_list mutexes;
    
    boost::indirect_iterator<mutex_list::iterator> first(mutexes.begin()), last(mutexes.end());
    boost::lock(first, last);
}
