#include <iostream>
#include <utility>

/// YOUR STUFF:

template <class, std::size_t> struct Vec {};

template<class T> void f1(int a1)
{
    std::cout << "f1 with "<<a1<<" called, " << __PRETTY_FUNCTION__ << '\n';
}

template<class T> void f2(double a1, int a2) {
    std::cout << "f2 with " << a1 << ", " << a2 << " called, " << __PRETTY_FUNCTION__ << std::endl;
}

/// /////////////////////////////////

template <class...> struct type_list {};

// Provide a sensible maximum:
template <template <class...> class F, typename T, std::size_t... indices, typename... Args>
void callImpl( std::index_sequence<indices...>, std::size_t n, Args&&... args )
{
    static constexpr decltype(&F<Vec<T, 0>>::call) array[] = { &F<Vec<T, indices>>::call... };
    array[n]( std::forward<Args>(args)... );
}

template <template <class...> class F, typename T, typename... Args>
void call( std::size_t n, Args&&... args )
{
    callImpl<F, T>( std::make_index_sequence<10>(), n, std::forward<Args>(args)... );
}

template <template <class...> class F, typename firstType, typename... types, typename... Args>
void callWithType( std::size_t tid, std::size_t n, type_list<firstType, types...>, Args&&... args )
{
    static constexpr decltype(call<F, firstType, Args...>)* arr[]
    { call<F, firstType, Args...>, call<F, types, Args...>... };

    arr[tid]( n, std::forward<Args>(args)... );
}

template <typename T>
struct f1_template
{ static void call(int a1) {f1<T>(a1);} };

template <typename T>
struct f2_template
{ static void call(double a1, int a2) {f2<T>(a1, a2);} };

void f1(int tid, int n, int a1)
{
    callWithType<f1_template>( tid, n, type_list<int, double, std::string>{}, a1 );
}

void f2(int tid, int n, double a1, double a2)
{
	callWithType<f2_template>( tid, n, type_list<int, double, std::string>{}, a1, a2 );
}

int main()
{
    f1(1, 2, 3);
    f2(2, 0, 3., 5.);
}
