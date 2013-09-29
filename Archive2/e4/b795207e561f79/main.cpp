#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<size_t Len, size_t Alignment>
using aligned_storage_t = typename std::aligned_storage<Len, Alignment>::type;

constexpr size_t max_impl(size_t acc) {
    return acc;
}
template<class Num, class ...Nums>
constexpr size_t max_impl(size_t acc, Num num, Nums... nums) {
    return (num > acc) ? max_impl(num, nums...) : max_impl(acc, nums...);
}
template<class ...Nums>
constexpr size_t max(Nums... nums) {
    return max_impl(0U, nums...);
}

template<class ...Args>
class storage {
    aligned_storage_t<max(sizeof(Args)...), max(std::alignment_of<Args>::value...)> data;
public:
    void* get() {
        return &data;
    }
    operator void* () {
        return get();
    }
    
    template<class T, class ...CArgs>
    void construct(CArgs&&... args) {
        new (*this) T (std::forward<CArgs>(args)...);
    }
    
    template<class T>
    void destruct(typename std::enable_if<std::is_class<T>::value>::type* = nullptr) {
        static_cast<T*>(static_cast<void*>(*this))->~T();
    }
    template<class T>
    void destruct(typename std::enable_if<!std::is_class<T>::value>::type* = nullptr) {}
};

int main()
{
    storage<int, std::string, std::vector<int>> store;
    std::cerr << sizeof(store) << std::endl;
    auto str = new (store) std::string("Hello world");
    std::cerr << *str << std::endl;
    store.destruct<std::string>();
    auto vec = new (store) std::vector<int>{ 1, 2, 3, 4 }; 
    std::cerr << vec->front() << std::endl;
    store.destruct<std::vector<int>>();
    store.
}
