#include <iostream>

template < std::size_t... INDICES > struct index_list ;

template < std::size_t N > struct index_list<N>
{
    static std::ostream& print( std::ostream& stm = std::cout )
    { return stm << N << ' ' ; }
};

template < std::size_t FIRST, std::size_t... REST > struct index_list< FIRST, REST... >
{
    static std::ostream& print( std::ostream& stm = std::cout )
    { index_list<FIRST>::print(stm) ; return index_list<REST...>::print(stm) ; }
};

template < std::size_t, typename, std::size_t... > struct push_back ;
template < std::size_t N > struct push_back< N, index_list<> >
{ using type = index_list<N> ; } ;
template < std::size_t N, std::size_t... I > struct push_back< N, index_list<I...> >
{ using type = index_list<I...,N> ; } ;

template < typename, std::size_t... > struct pop_front ;
template < std::size_t N > struct pop_front< index_list<N> >
{ using type = index_list<> ; } ;
template < std::size_t FIRST, std::size_t... REST >
struct pop_front< index_list<FIRST,REST...> > { using type = index_list<REST...> ; } ;

template < typename, std::size_t... > struct rotate ;
template <> struct rotate< index_list<> > { using type = index_list<> ; } ;
template < std::size_t FIRST, std::size_t... REST >
struct rotate< index_list<FIRST,REST...> > { using type = index_list<REST...,FIRST> ; } ;

template < std::size_t, typename, std::size_t... > struct fold ;
template < std::size_t N> struct fold< N, index_list<> > { using type = index_list<> ; } ;
template < std::size_t N, std::size_t FIRST, std::size_t... REST >
struct fold< N, index_list<FIRST,REST...> >
{
    using type = typename push_back< FIRST,
                             typename fold< N-1, index_list<REST...> >::type >::type ;
} ;
template < typename std::size_t FIRST, std::size_t... REST >
struct fold< 0, index_list<FIRST,REST...> > { using type = index_list<FIRST,REST...> ; };

template < typename, std::size_t... > struct reverse ;
template <> struct reverse< index_list<> > { using type = index_list<> ; } ;
template < std::size_t FIRST, size_t... REST > struct reverse< index_list<FIRST,REST...> >
{ using type = typename push_back< FIRST,
                     typename reverse< index_list<REST...> >::type >::type ;
} ;

int main()
{
    using ilist = index_list<0,1,2,3,4,5,6,7,8,9> ;
    ilist::print() << '\n' ;

    using ilist2 = push_back<10,ilist>::type ;
    ilist2::print() << '\n' ;

    using ilist3 = pop_front<ilist2>::type ;
    ilist3::print() << '\n' ;

    using ilist4 = fold< 5, ilist3 >::type ;
    ilist4::print() << '\n' ;

    using ilist5 = reverse<ilist4>::type ;
    ilist5::print() << '\n' ;

    reverse<
               fold<
                      5,
                      pop_front<
                                   push_back<
                                                10,
                                                index_list<0,1,2,3,4,5,6,7,8,9>
                                            >::type
                                >::type
                    >::type
            >::type::print( std::cout << "\ncomposed inline:\n" ) << '\n' ;
}
