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
	stuff<int> s(42);
}