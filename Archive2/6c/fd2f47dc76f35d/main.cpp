#include <type_traits>

//used to rebind templates
template<class T, class C>
struct rebinder;
template<class T, template<class> class C, class U>
struct rebinder<T, C<U>> {using type = C<T>;};


//contains Yin<void> or Yang<void>
template<class T>
struct mutual_recursion;


//here's Yin + Specialization
template <typename T>
struct Yin {
    T *m_ptr;
};

template <template<class> class other>
struct Yin<other<void>> 
{
    other<Yin<void>> *m_ptr;
};


//here's Yang + Specialization
template <typename T>
struct Yang {
    T *m_ptr;
}; 
template <template<class> class other>
struct Yang<other<void>> 
{
    other<Yang<void>> *m_ptr;
};

//proof of type correctness and recursability
int main() {
    Yin<Yang<void>> a {}; 
    Yang<Yin<void>> b {};
    a.m_ptr = &b;
    b.m_ptr = &a;
    //proof of recursion
    auto ptr = a.m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr->m_ptr;
    (void)ptr;
    return 0;
}