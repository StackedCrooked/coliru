#include <iostream>
#include <utility>

/// YOUR STUFF:

template <class, std::size_t> struct Vec {};

template<class T> void f1(int a1)
{
    std::cout << "f1 with "<<a1<<" called, " << __PRETTY_FUNCTION__ << '\n';
}

/// /////////////////////////////////

template <class...> struct type_list {};

// Provide a sensible maximum:
template <typename T, std::size_t... indices, typename... Args>
void callImpl( std::index_sequence<indices...>, std::size_t n, Args&&... args )
{
    static constexpr decltype(f1<Vec<T, 0>>)* array[] = { f1<Vec<T, indices>>... };
	array[n]( std::forward<Args>(args)... );
}

template <typename T, typename... Args>
void call( std::size_t n, Args&&... args )
{
    callImpl<T>( std::make_index_sequence<10>(), n, std::forward<Args>(args)... );
}

template <typename firstType, typename... types, typename... Args>
void callWithType( std::size_t tid, std::size_t n, type_list<firstType, types...>, Args&&... args )
{
    static constexpr decltype(call<firstType, Args...>)* arr[]
    { call<firstType, Args...>, call<types, Args...>... };

    arr[tid]( n, std::forward<Args>(args)... );
}

void f1(int tid, int n, int a1)
{
    callWithType( tid, n, type_list<int, double, std::string>{}, a1 );
}

int main()
{
    f1(1, 2, 3);
    f1(2, 0, 3);
}
