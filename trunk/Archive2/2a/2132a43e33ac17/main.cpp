#include <list>
#include <vector>
#include <iostream>
#include <chrono>
 
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

template<typename _Type, typename _Alloc=std::allocator<_Type>,
         template<typename,typename> class sequence_container = std::list>
class chunk_allocator
{
public:
  using object = _Type;
  using object_allocator = _Alloc;
  using object_container = std::vector<object,object_allocator>;
  using size_type = typename object_container::size_type;
private:
  struct chunk  // deriving from object_container would be simpler ...
  { 
    object_container objects;
    size_type size;
    size_type capacity() const
    { return objects.size(); }
    chunk(size_type capacity, const object_allocator&alloc)
    : objects(capacity,alloc), size(0) {}
    object*get(size_type n) noexcept
    {
      object*ptr=nullptr;
      if(size+n <= capacity()) {
        ptr = objects.data()+size;
        size+= n;
      }
      return ptr;
    }
  };
  using chunk_alloc = typename object_allocator::template rebind<chunk>::other;
  using chunk_container = sequence_container<chunk,chunk_alloc>;
  using chunk_iterator = typename chunk_container::iterator;
  chunk_container chunks;
public:
  /// allow move
  chunk_allocator(chunk_allocator&&) = default;
  chunk_allocator&operator=(chunk_allocator&&) = default;
  /// constructor from size = initial capacity
  explicit chunk_allocator(size_type initial_chunk_size,
                           object_allocator const&alloc=object_allocator())
    : chunks()
    , last_chunk(chunks.emplace(chunks.end(),initial_chunk_size,alloc)) {}
  chunk_iterator last_chunk;
  /// no default constructor
  chunk_allocator() = delete;
  /// no copy
  chunk_allocator(chunk_allocator const&) = delete;
  chunk_allocator&operator=(chunk_allocator const&) = delete;
  /// obtain contiguous chunks of objects
  /// \param[in] n          \# objects in returned chunk
  /// \param[in] chunk_size \# objects to allocate should we not have enough
  /// \return pointer to first of n contiguous objects
  object*create(const size_type n, size_type chunk_size=0)
  {
    if(n==0)
      return nullptr;
    auto ptr = last_chunk->get(n);
    if(ptr==nullptr) {
      if(chunk_size==0) chunk_size = last_chunk->capacity();
      if(chunk_size< n) chunk_size = n;
      last_chunk = chunks.emplace(chunks.end(),chunk_size,
                                  last_chunk->objects.get_allocator());
      ptr = last_chunk->get(n);
    }
    return ptr;
  }
  /// for testing
  void report()
  {
    std::cout<<"chunk_allocator:\n";
    for(auto const&c:chunks)
      std::cout<< " chunk has first=" << c.objects.data()
               << " size="<<c.size
               << " capacity="<<c.capacity()<<'\n';
  }
};
// testing now:
    struct foo
    {
      int X;
      static int C;
      foo() : X(C++) {}
      foo(foo const&) = delete;
      foo&operator=(foo const&) = delete;
      foo(foo &&) = delete;
      foo&operator=(foo &&) = delete;
    };    
    int foo::C=0;    
    int main()
    {
        chunk_allocator<foo> C(3);
        auto a = C.create(1);
        auto b = C.create(4);
        auto c = C.create(3);        
        std::cout<<" a="<<a<<" a->X = "<<a->X<<'\n'
                 <<" b="<<b<<" b->X = "<<b->X<<'\n'
                 <<" c="<<c<<" c->X = "<<c->X<<'\n';
      
        steady_clock::time_point start = steady_clock::now();
    
        size_t create_size = 1e5;
        size_t iterations  = 1e2;
    
        for( size_t x = 0; x < iterations; ++x ) {
            C.create( create_size );
        }
    
        steady_clock::time_point end = steady_clock::now();
    
        std::cout << "\nCreating " << iterations << " times by " << create_size << " and initializing the Elements took "
            << duration_cast<milliseconds>(end - start).count()
            << " msec.\n";
    }
