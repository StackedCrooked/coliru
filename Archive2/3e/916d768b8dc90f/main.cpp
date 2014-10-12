#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>

using namespace boost::interprocess;

//Typedefs of allocators and containers
typedef managed_shared_memory::segment_manager                       segment_manager_t;
typedef allocator<void, segment_manager_t>                           void_allocator;
typedef allocator<int, segment_manager_t>                            int_allocator;
typedef vector<int, int_allocator>                                   int_vector;
typedef allocator<char, segment_manager_t>                           char_allocator;
typedef basic_string<char, std::char_traits<char>, char_allocator>   char_string;

class complex_data
{
public:
   int               id_;
   char_string       char_string_;
   int_vector int_vector_;

   //Since void_allocator is convertible to any other allocator<T>, we can simplify
   //the initialization taking just one allocator for all inner containers.
   complex_data(const void_allocator &void_alloc)
      : id_(-1), char_string_(void_alloc), int_vector_(void_alloc)
   {}

   //Other members...
};


typedef allocator<complex_data, segment_manager_t>     complex_data_allocator;
typedef vector<complex_data, complex_data_allocator>   complex_data_vector;

template <typename V, typename Element /*= typename V::value_type*/>
static inline void resize(V& vect, size_t newsize, Element const& element) {
    if (vect.size() < newsize)
    {
        vect.insert(
                vect.end(), 
                newsize - vect.size(), 
                element
                );
    } else
    {
        vect.erase(
                std::next(vect.begin(), newsize), 
                vect.end()
                );
    }
}

template <typename V>
static inline void resize(V& vect, size_t newsize, typename V::allocator_type const& alloc_inst) {
    resize(vect, newsize, typename V::value_type(alloc_inst));
}

template <typename V>
static inline void resize(V& vect, size_t newsize) {
    resize(vect, newsize, typename V::value_type(vect.get_allocator()));
}

int main ()
{
    //Remove shared memory on construction and destruction
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    //Create shared memory
    managed_shared_memory segment(create_only,"MySharedMemory", 65536);

    //An allocator convertible to any allocator<T, segment_manager_t> type
    void_allocator alloc_inst (segment.get_segment_manager());

    //Construct the shared memory map and fill it
    complex_data *complex_data0_ = segment.construct<complex_data> ("MyCompexData")(alloc_inst);

    complex_data0_->char_string_ = "Hello Wold";
    complex_data0_->int_vector_.push_back(3);

    complex_data *complex_data1_ = segment.find_or_construct<complex_data> ("MyCompexData")(alloc_inst);
    complex_data1_->int_vector_.push_back(6);

    std::cout << complex_data1_->id_ << ", " << complex_data0_->char_string_;
    for(size_t i = 0; i < complex_data1_->int_vector_.size(); i++) std::cout << ", " << complex_data1_->int_vector_[i];


    complex_data_vector *complex_data_vector0 = segment.construct<complex_data_vector> ("MyCompexDataVector")(alloc_inst);

    // The different approaches from the answer:
    //
    // #1.
    complex_data_vector0->clear();
    complex_data_vector0->insert(complex_data_vector0->end(), 3, complex_data(alloc_inst));

    // #2.
    *complex_data_vector0 = { 3, complex_data(alloc_inst), alloc_inst };

    // #3.
    complex_data_vector tmp { 3, complex_data(alloc_inst), alloc_inst };
    complex_data_vector0->assign(tmp.begin(), tmp.end()); // use `std::make_move_iterator` for moves

    // #4.
    resize(*complex_data_vector0, 3, complex_data(alloc_inst));
    resize(*complex_data_vector0, 3, alloc_inst);
    resize(*complex_data_vector0, 3);
}
