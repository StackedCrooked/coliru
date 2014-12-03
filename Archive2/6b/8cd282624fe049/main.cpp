template<class T>
struct stuff
{
    stuff(T WUB);
};

template<class T>
inline stuff<T>::stuff(T WUB){}

struct WUB{};

int main()
{
	stuff<int> s(42);   // warning C4224: nonstandard extension used : formal parameter 'WUB' was previously defined as a type
                        //source\main.cpp(19) : while compiling class template member function 'stuff<T>::stuff(T)'
}