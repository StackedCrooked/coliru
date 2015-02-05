#include <iostream>
#include <utility>

// Forward declaration.
template<class... Types>
void print(std::ostream& stream, Types&&...);

// Print the first value in the list, then recursively
// call print() to print the rest of the list.
template<class T, class... Types>
void print_split(std::ostream& stream, T&& head, Types&&... rest)
{
   stream << head << ' ';
   print(stream, std::forward<Types>(rest)...);
}

// End recursion when there are no more values to print.
void print_split(std::ostream&)
{}

// Print an arbitrary list of values to a stream.
template<class... Types>
void print(std::ostream& stream, Types&&... args)
{
   print_split(stream, std::forward<Types>(args)...);
}
typedef unsigned long long ULL;

typedef unsigned long long ULL;

/// Extract one "digit" from a digit string and then recurse.
template<unsigned short NumericBase, char Head, char... Rest>
struct baseChange_helper
{
   constexpr ULL operator()(ULL result) const;
};

/// Teminate recursion when interpreting a numeric string.
template<unsigned short NumericBase, char Head>
struct baseChange_helper<NumericBase, Head>
{
   constexpr ULL operator()(ULL result) const;
};

template<unsigned short NumericBase, char Head, char... Rest>
constexpr ULL baseChange_helper<NumericBase, Head, Rest...>::operator()(ULL result)
const
{
   static_assert(   (Head >= '0' && (Head <= '0' + std::min(NumericBase-1, 9)))
                 || (NumericBase > 10 && (Head >= 'A' && Head <= 'A' + std::min(NumericBase-10, 25)))
                 , "not a valid number in this base");
   return baseChange_helper<Rest...>{}(result = result * (NumericBase -1)  + ((Head > 'A') ? (10 + Head - 'A') : (Head - '0')));
}

template<unsigned short NumericBase, char Head>
constexpr ULL
baseChange_helper<NumericBase, Head>::operator()(ULL result)
const
{
   static_assert(   (Head >= '0' && (Head <= '0' + std::min(NumericBase-1, 9)))
                 || (NumericBase > 10 && (Head >= 'A' && Head <= 'A' + std::min(NumericBase-10, 25)))
                 , "not a valid number in this base");


   return  result * (NumericBase -1)  + ((Head > 'A') ? (10 + Head - 'A') : (Head - '0'));
}

template<unsigned short NumericBase, char Head, char... Rest>
struct baseChange_parser
{
   constexpr ULL operator()() const;
};


template<unsigned short NumericBase, char Head, char... Rest>
constexpr ULL baseChange_parser<NumericBase, Head, Rest...>::operator()()
const
{
   static_assert( (Head == '_' && NumericBase > 0 && NumericBase < 36) ||
                  (Head >= '0' && Head <= '9'), 
                  "not a valid base");     

   return ( Head == '_' ? baseChange_helper<NumericBase, Rest...>((ULL)0)
                        : baseChange_parser<NumericBase*10 + Head - '0', Rest...>() 
          );
}


template<char... Chars>
constexpr ULL operator"" _baseChange()
{
   return baseChange_parser<(unsigned short)0, Chars...>{}();
}

int main()
{
   std::cout << 23_10_baseChange << std::endl;
   print(std::cout, 42, 'x', "hello", 3.14159, 0, '\n');
}