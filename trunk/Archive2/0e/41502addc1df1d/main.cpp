#include <iostream>
#include <thread>
#include <atomic>
 

template <char...chars>
std::enable_if_t<sizeof...(chars) == 0> printChars()
{
}

template <char firstChar, char...restChars>
void printChars()
{
    std::cout << firstChar;
    printChars<restChars...>();
}

template <typename T, T...ints>
void doSomething(const std::integer_sequence<T, ints...>& sequence)
{
    printChars<ints...>();
    std::cout << std::endl;
}

/*constexpr auto buildString(const char* str)
{
    return 0;
}*/

namespace detail
{
   /* template <typename T, T AppendInt, T...RestInts>
    struct ingeger_sequence_concatenate_helper
    {
        typedef std::integer_sequence<RestInts..., AppendInt> type;  
    };
    
    template <typename T, T AppendInt, typename ISType, typename...RestInts>
    struct integer_sequence_concatenate_helper<*/
    
    template <typename ISType, typename T, T AppendInt>
    struct integer_sequence_concat_helper;
    
    template <typename T, T AppendInt, T...ISInts>
    struct integer_sequence_concat_helper<std::integer_sequence<T, ISInts...>, T, AppendInt>
    {
      typedef std::integer_sequence<AppendInt, ISInts...> type;  
    };
}

template <typename SequenceType, typename T, T AppendInt>
struct integer_sequence_concatenate
{
    typedef detail::integer_sequence_concat_helper<SequenceType, T, AppendInt> type;
    
};

int main(int argc, char* argv[])
{
    std::integer_sequence<char, 'h', 'i'> intSequence;
    doSomething(intSequence);
}