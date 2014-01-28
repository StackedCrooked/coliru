template<class T, size_t max>
struct localarray;

template<class T>
struct localarray<T,0> {
    //all of vector's interface except no constructors, and no copy/move assignment
    //reserve does nothing, if resize runs out of capacity, throws std::bad_alloc
    
    //are these legal?
    T* data() {return reinterpret_cast<T*>(&buffer);}
    const T* data() const {return reinterpret_cast<const T*>(&buffer);}
private:
    explicit localarray(unsigned max_count_) : count(0), max_count(max_count_) {}
    localarray(const localarray&) = delete;
    localarray(localarray&&) = delete;
    localarray& operator=(const localarray&) = delete;
    localarray& operator=(localarray&&) = delete;
    
    unsigned count;
    unsigned max_count;
    std::aligned_storage<sizeof(T), alignof(T)> buffer;
};
template<class T, size_t max>
struct localarray : public localarray<T,0> {
    localarray() : localarray<T,0>(max) {}
    localarray(const localarray& rhs) = delete;
    localarray(localarray&& rhs) = delete;
    localarray(std::initializer_list<T> list) : localarray<T,0>(max) {assign(list);}   
    explicit localarray(unsigned count) : localarray<T,0>(max) {assign(count);}
    explicit localarray(unsigned count, const T& val) : localarray<T,0>(max) {assign(count, val);}
    
    localarray& operator=(const localarray& rhs) = delete;
    localarray& operator=(localarray&& rhs) = delete;
private:
    char morebuffer[max-1*sizeof(T)];
};

int main() {
    
}