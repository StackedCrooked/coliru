
#include <iostream>

//mystery C API
void c_lib_function(int** ptr) {*ptr = new int(3); std::cout << "allocate\n";}
void c_lib_free(int* ptr) {delete ptr; std::cout << "deallocate\n";}



//ptrptr magic
#include <memory>

template<class T, class deleter>
class ptrptr_type {
public:
    ptrptr_type(std::unique_ptr<T, deleter>& ptr) : uptr(&ptr), tptr(ptr.get()) {ptr.release();}
    ~ptrptr_type() {uptr->reset(tptr);}
    operator T**(){return &tptr;}
private:
    std::unique_ptr<T, deleter>* uptr;
    T* tptr;
};
template<class T, class D>
ptrptr_type<T,D> ptrptr(std::unique_ptr<T, D>& ptr) { return {ptr};}




//your code
struct c_free_wrapper {
    template<class T>
    void operator()(T* ptr) {c_lib_free(ptr);}
};
typedef std::unique_ptr<int, c_free_wrapper> mystery_ptr;

int main() {
    mystery_ptr my_ptr;
    c_lib_function(ptrptr(my_ptr));
    std::cout << *my_ptr << '\n';
}