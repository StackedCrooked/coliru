template<class T>
struct ref_wrapper;

template<class T>
ref_wrapper<T> ref(T&);

template<class T>
struct ref_wrapper
{
    template<class U>
    ref_wrapper(U&)
    {  static_assert(sizeof(U)==0, "explicit ref() required"); }
    
    T& get() { return *m; }
    
private:
    explicit ref_wrapper(T& p) : m(&p) {}
    T* m;
    
    friend ref_wrapper ref<T>(T&);
};

template<class T>
ref_wrapper<T> ref(T& p) { return ref_wrapper<T>{p}; }

void modify(ref_wrapper<int> i)
{
    i.get() = 42;
}

#include <iostream>
int main()
{
    int i = 0;
    modify(i);
    modify(ref(i));
    std::cout << i << '\n';
}