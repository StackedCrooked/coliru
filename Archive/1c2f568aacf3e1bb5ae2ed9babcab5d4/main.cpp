template<typename T>
struct Outer { struct Inner {}; };

template<typename T>
struct Traits;

template<typename T>
struct Traits< typename Outer<T>::Inner >
{
};


template<typename T>
struct Outer { using Inner = int; }; // now what, bitches?

int main()
{
}