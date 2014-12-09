#include <iterator>
#include <iostream>

// Utility typedef template for output iterator SFINAE
template<typename OutputIt,
    typename Tag = typename std::iterator_traits<OutputIt>::iterator_category>
using is_output_iterator = typename std::enable_if<
        std::is_same<Tag, std::output_iterator_tag>::value
        >::type;

// Use is_output_iterator
template<typename OutputIt,
         typename = is_output_iterator<OutputIt>>
OutputIt test(char32_t v, OutputIt output)
{
    *output++ = v;
    return output;
}

// SFINAE

template<typename OutputIt,
         typename Tag = typename std::iterator_traits<OutputIt>::iterator_category,
         typename = typename std::enable_if<std::is_same<Tag, std::output_iterator_tag>::value>::type>
OutputIt test2(char32_t v, OutputIt output)
{
    *output++ = v;
    return output;
}

// Tag dispatch

template<typename OutputIt>
OutputIt test3(char32_t v, OutputIt output)
{
    return test3(v, output, typename std::iterator_traits<OutputIt>::iterator_category());
}

template<typename OutputIt>
OutputIt test3(char32_t v, OutputIt output, std::output_iterator_tag)
{
    *output++ = v;
    return output;
}

int main()
{
    test('A', std::ostream_iterator<char>(std::cout));
    test2('B', std::ostream_iterator<char>(std::cout));
    test3('C', std::ostream_iterator<char>(std::cout));
}
