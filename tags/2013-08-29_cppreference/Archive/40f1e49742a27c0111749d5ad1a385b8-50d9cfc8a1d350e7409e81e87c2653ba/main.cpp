    #include <iostream>
    
    template<class T> class B;
    
    template <class T>
    class A
    {
        B<T>* b;    
    };
    
    
    template <class T>
    class B
    {
        A<T>* a;    
    };
    
    int main()
    {
        A<B<int>> a;
        B<A<float>> b;
    }