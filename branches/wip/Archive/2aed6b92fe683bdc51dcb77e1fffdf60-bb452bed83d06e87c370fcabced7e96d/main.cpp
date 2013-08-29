    #include <type_traits>
    #include <vector>
    #include <iterator>
    #include <iostream>
    
    template<typename C,typename=void> struct can_reserve: std::false_type {};
    
    template<typename T, typename A>
    struct can_reserve<std::vector<T,A>,void>:
        std::true_type
    {};
    
    template<int n> struct secret_enum { enum class type {instance}; };
    template<int n>
    using SecretEnum = typename secret_enum<n>::type;
    
    template<bool b, int override_num=1>
    using EnableFuncIf = typename std::enable_if< b, SecretEnum<override_num> >::type;
    template<bool b, int override_num=1>
    using DisableFuncIf = EnableFuncIf< !b, -override_num >;
    
    template<typename C >
    auto try_reserve( C& c, std::size_t n )->decltype( c.reserve(n) ) {
      return c.reserve(n);
    }
    template<typename C >
    void try_reserve( C& c, ... ) { } // do nothing
    
    template<typename C,typename=void>
    struct has_size_method:std::false_type {};
    template<typename C>
    struct has_size_method<C, typename std::enable_if<std::is_same<
      decltype( std::declval<C>().size() ),
      decltype( std::declval<C>().size() )
    >::value>::type>:std::true_type {};
    
    namespace adl_aux {
      using std::begin; using std::end;
      template<typename C>
      auto adl_begin(C&&c)->decltype( begin(std::forward<C>(c)) );
      template<typename C>
      auto adl_end(C&&c)->decltype( end(std::forward<C>(c)) );
    }
    template<typename C>
    struct iterable_traits {
        typedef decltype( adl_aux::adl_begin(std::declval<C&>()) ) iterator;
        typedef decltype( adl_aux::adl_begin(std::declval<C const&>()) ) const_iterator;
    };
    template<typename C> using Iterator = typename iterable_traits<C>::iterator;
    template<typename C> using ConstIterator = typename iterable_traits<C>::const_iterator;
    template<typename I> using IteratorCategory = typename std::iterator_traits<I>::iterator_category;
    
    template<typename C, EnableFuncIf< has_size_method<C>::value, 1> =SecretEnum<1>::instance >
    std::size_t size_at_least( C&& c ) {
        return c.size();
    }
    
    template<typename C, EnableFuncIf< !has_size_method<C>::value &&
      std::is_base_of< std::random_access_iterator_tag, IteratorCategory<Iterator<C>> >::value, 2> =SecretEnum<2>::instance >
    std::size_t size_at_least( C&& c ) {
        using std::begin; using std::end;
      return end(c)-begin(c);
    };
    template<typename C, EnableFuncIf< !has_size_method<C>::value &&
      !std::is_base_of< std::random_access_iterator_tag, IteratorCategory<Iterator<C>> >::value, 3> =SecretEnum<3>::instance >
    std::size_t size_at_least( C&& c ) {
      return 0;
    };
    
    template < typename It >
    auto try_make_move_iterator(It i, std::true_type)
    -> decltype(make_move_iterator(i))
    {
        return make_move_iterator(i);
    }
    template < typename It >
    It try_make_move_iterator(It i, ...)
    {
        return i;
    }
    
    
    #include <iostream>
    template<typename C1, typename C2>
    C1&& append_containers( C1&& c1, C2&& c2 )
    {
      using std::begin; using std::end;
      try_reserve( c1, size_at_least(c1) + size_at_least(c2) );
      
      using is_rvref = std::is_rvalue_reference<C2&&>;
      c1.insert( end(c1),
                 try_make_move_iterator(begin(c2), is_rvref{}),
                 try_make_move_iterator(end(c2), is_rvref{}) );
      
      return std::forward<C1>(c1);
    }
    
    struct append_infix_op {} append;
    template<typename LHS>
    struct append_on_right_op {
      LHS lhs;
      template<typename RHS>
      LHS&& operator=( RHS&& rhs ) {
        return append_containers( std::forward<LHS>(lhs), std::forward<RHS>(rhs) );
      }
    };
    
    template<typename LHS>
    append_on_right_op<LHS> operator+( LHS&& lhs, append_infix_op ) {
      return { std::forward<LHS>(lhs) };
    }
    template<typename LHS,typename RHS>
    typename std::remove_reference<LHS>::type operator+( append_on_right_op<LHS>&& lhs, RHS&& rhs ) {
      typename std::decay<LHS>::type retval = std::forward<LHS>(lhs.lhs);
      return append_containers( std::move(retval), std::forward<RHS>(rhs) );
    }
    
    template<typename C>
    void print_container( C&& c ) {
      for( auto&& x:c )
        std::cout << x << ",";
      std::cout << "\n";
    };
    
    int main() {
      std::vector<int> a = {0,1,2};
      std::vector<int> b = {3,4,5};
      print_container(a);
      print_container(b);
      a +append= b;
      const int arr[] = {6,7,8};
      a +append= arr;
      print_container(a);
      print_container(b);
      std::vector<double> d = ( std::vector<double>{-3.14, -2, -1} +append= a );
      print_container(d);
      std::vector<double> c = std::move(d) +append+ a;
      print_container(c);
      print_container(d);
      std::vector<double> e = c +append+ std::move(a);
      print_container(e);
      print_container(a);
    }
    
