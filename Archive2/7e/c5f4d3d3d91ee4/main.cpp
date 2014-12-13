#include <iostream> /* std::cout*/
#include <functional> /* pour le test */
#include <tuple>
#include <utility> /* std::index_sequence (C++14 uniquement) */

namespace newstd
{
    /* =( Pas de C++14? utilisez newstd! */
    template<std::size_t... Seq>
    struct index_sequence{};
    
    /* helper */
    template<std::size_t N, std::size_t... S>
    struct seq: seq<N-1,N-1, S...>{};
    template<std::size_t... S>
    struct seq<0, S...>
    { typedef index_sequence<S...> type; };
    
    /* pour garder les même noms standards */
    template<std::size_t N>
    using make_index_sequence= typename seq<N>::type;
    template<typename... T>
    using index_sequence_for = make_index_sequence<sizeof...(T)>;
}

template<typename F, typename... ArgsT, std::size_t... Seq>
typename std::result_of<F(ArgsT...)>::type NzImplTupleUnpack(F&& func, std::tuple<ArgsT...>&& /*à ne pas remplacer par une reference constante*/ t,
                                                            newstd::index_sequence<Seq...>/* pas besoin de nom */)
{
    return func(std::forward<ArgsT>(std::get<Seq>(t))...);
}

template<typename F, typename... ArgsT>
typename std::result_of<F(ArgsT...)>::type/* on peut eventuellement prendre une valeur de retour */
    NzUnpackTuple(F&& /*universal reference*/ func, std::tuple<ArgsT...>&& /*universal reference, encore*/ t)
{
    return NzImplTupleUnpack(std::forward<F>(func), /* toujours le "std::forward" */
                             std::forward<std::tuple<ArgsT...>>(t),
                             newstd::index_sequence_for<ArgsT...>{}); /* sequence: std::index_sequence<0,1,2,...,taille du tuple-1>*/
}

unsigned int test_function(unsigned int x,unsigned int y)
{
    return x*y;
}

int main()
{
    int t=2;
    NzUnpackTuple( /* marche avec des lambdas avec captures et retournant void */
        [&t](int x, int y, int z)
        {
            std::cout<<x+y+z-(t++)<<std::endl;
        },
    std::make_tuple(1,2,3));
    
    std::cout<< NzUnpackTuple( /* marche aussi avec des pointeurs/references de fonctions */
            test_function,
            std::make_tuple(6,2))<<std::endl;
    
    std::cout<< NzUnpackTuple( /* et ça marche bien évidemment aussi avec std::function et les Objets-functions*/
            std::function<decltype(test_function)>(test_function),
            std::make_tuple(t,2))<<std::endl;
    
    struct A
    {
        void f() const
        {
            std::cout<< x<<std::endl;
        }
        int x=5;
    };
    
    /* Il faut surcharger pour étendre ça aux fonctions membres */
}
