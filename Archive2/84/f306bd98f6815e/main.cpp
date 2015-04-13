#include <boost/interprocess/managed_mapped_file.hpp>

namespace bi = boost::interprocess;

int main() {
    std::string vecFile = "vector.dat";
    bi::managed_mapped_file file_vec(bi::open_or_create,vecFile.c_str(), 1000);

    typedef bi::allocator<int, bi::managed_mapped_file::segment_manager> int_alloc;
    typedef std::vector<int, int_alloc>  MyVec;

    MyVec * vecptr = file_vec.find_or_construct<MyVec>("myvector")(file_vec.get_segment_manager());
    
    vecptr->push_back(rand());
}
