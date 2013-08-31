template<typename T>
struct Outer { struct Inner {}; };

template<typename T>
struct Traits;

template<typename T>
struct Traits< typename Outer<T>::Inner >
{
};


template<>
struct Outer<int> { using Inner = int; }; // now what, bitches?
template<>
struct Outer<double> { using Inner = int; }; // now what, bitches?

int main()
{
}