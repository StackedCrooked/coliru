#include <vector>
#include <chrono>
#include <iostream>
#include <unordered_map>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

static const int MaxMemorySize = 800000;
static int FreedMemory = 0;
static int AllocatorCalls = 0;
static int DeallocatorCalls = 0;
template <typename T>
class LocalAllocator
{
  public:
      std::vector<char>* memory;
      int* CurrentUsed;
      typedef T value_type;
      typedef value_type * pointer;
      typedef const value_type * const_pointer;
      typedef value_type & reference;
      typedef const value_type & const_reference;
      typedef std::size_t size_type;
      typedef std::size_t difference_type;

    template <typename U> struct rebind { typedef LocalAllocator<U> other; };

    template <typename U>
    LocalAllocator(const LocalAllocator<U>& other) {
        CurrentUsed = other.CurrentUsed;
        memory = other.memory;
    }
    LocalAllocator(std::vector<char>* ptr, int* used) {
        CurrentUsed = used;
        memory = ptr;
    }
    template<typename U> LocalAllocator(LocalAllocator<U>&& other) {
        CurrentUsed = other.CurrentUsed;
        memory = other.memory;
    }
    pointer address(reference r) { return &r; }
    const_pointer address(const_reference r) { return &r; }
    size_type max_size() const { return MaxMemorySize; }
    void construct(pointer ptr, value_type&& t) { new (ptr) T(std::move(t)); }
    void construct(pointer ptr, const value_type & t) { new (ptr) T(t); }
    void destroy(pointer ptr) { static_cast<T*>(ptr)->~T(); }

    bool operator==(const LocalAllocator& other) const { return memory == other.Memory; }
    bool operator!=(const LocalAllocator&) const { return false; }

    pointer allocate(size_type count) {
        AllocatorCalls++;
        if (*CurrentUsed + (count * sizeof(T)) > MaxMemorySize)
            throw std::bad_alloc();
        if (*CurrentUsed % std::alignment_of<T>::value) {
            *CurrentUsed += (std::alignment_of<T>::value - *CurrentUsed % std::alignment_of<T>::value);
        }
        auto val = &((*memory)[*CurrentUsed]);
        *CurrentUsed += (count * sizeof(T));
        return reinterpret_cast<pointer>(val);
    }
    void deallocate(pointer ptr, size_type n) {
        DeallocatorCalls++;
        FreedMemory += (n * sizeof(T));
    }

    pointer allocate() {
        return allocate(sizeof(T));
    }
    void deallocate(pointer ptr) {
        return deallocate(ptr, 1);
    }
};
int main() {

    std::vector<char> memory;
    int CurrentUsed = 0;
    memory.resize(MaxMemorySize);

    struct custom_hash {
        size_t operator()(int x) const { return x; }
    };
    std::unordered_map<int, int, custom_hash, std::equal_to<int>, LocalAllocator<std::pair<const int, int> > > dict(
        std::unordered_map<int, int>().bucket_count(),
        custom_hash(),
        std::equal_to<int>(),
        LocalAllocator<std::pair<const int, int>>(&memory, &CurrentUsed)
    );

    // start timer
    steady_clock::time_point start = steady_clock::now();

    for (int i=0;i<10000;i++)
        dict[i]=i;

    // stop timer
    steady_clock::time_point end = steady_clock::now();

    // compute and print the elapsed time in millisec
    std::cout << duration_cast<milliseconds>(end - start).count() << " ms insert time\n";
    int input;
    std::cin >> input; //don't want console to disappear
}
