#include <boost/circular_buffer.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>

namespace bip = boost::interprocess;

struct message {
    int data[32];
};

int main()
{
    bip::managed_mapped_file mmf(bip::open_or_create, "/tmp/circ_buffer.bin", 4ul << 10);
    typedef bip::allocator<message, bip::managed_mapped_file::segment_manager> allocator;

    boost::circular_buffer<message, allocator> instance(100, mmf.get_segment_manager());
}
