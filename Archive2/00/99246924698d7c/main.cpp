#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>

namespace bip = boost::interprocess;

using shared_vector = boost::interprocess::vector<int, bip::allocator<int, bip::managed_shared_memory::segment_manager> >;

int main()
{
    bip::managed_shared_memory shm(bip::open_or_create, "123123123123", 1<<10);
    auto smtmgr = shm.get_segment_manager();

    shared_vector v(smtmgr);
    v.push_back(1);
    v.push_back(2);
    v.clear();
    v.push_back(1);
    v.push_back(2);
    v.clear();
    v.push_back(1);
    v.push_back(2);
    v.clear();
    v.push_back(1);
    v.push_back(2);
    v.clear();
    v.push_back(1);
    v.push_back(2);
    v.clear();
}
