#include <iostream>
#include <string>
#include <vector>

template<class T>
struct aligned_pod {
    alignas(T) char data[sizeof(T)];
    
    void*       pvoid()       { return &data; }
    const void* pvoid() const { return &data; }
    T&       get()       { return *static_cast<T*>      (pvoid()); }
    const T& get() const { return *static_cast<const T*>(pvoid()); }
    operator const T& () const { return get(); }
    operator       T& ()       { return get(); }
    
    template<class ...Args>
    void construct(Args&&... args) {
        new (pvoid()) T(std::forward<Args>(args)...);
    }
    void destroy() { get().~T(); }
    
    friend std::ostream& operator<< (std::ostream& ost, const aligned_pod& pod) {
        return ost << pod.get();
    }
};

template<class Head, class ...Tail>
union un {
    aligned_pod<Head> head;
    un<Tail...> tail;
};

template<class Single>
union un<Single> {
    aligned_pod<Single> head;
};

template<class T>
class stack_option {
    aligned_pod<T> data;
    bool empty_ = true;
    
public:
    stack_option() = default;
    stack_option(const stack_option& other) : empty_(other.empty_) {
        if(!empty_) data.construct(other.get());    
    }
    stack_option(const T& data) : empty_(false) {
        this->data.construct(data);
    }
    ~stack_option() {
        if(!empty) data.destroy();
    }
    
    bool empty() {
        return empty_;
    }
};

int main()
{
    un<std::string, std::vector<int>, double> un;
    new (&un.head) std::string("Hi");
    std::cout << un.head << std::endl; 
    un.head.destroy();
    
    new (&un.tail.tail.head) double(1.3);
    std::cout << un.tail.tail.head << std::endl;
}
