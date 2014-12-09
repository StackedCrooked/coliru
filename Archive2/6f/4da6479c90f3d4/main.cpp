#include <iterator>
#include <iostream>

template<typename OutputIt,
         typename Tag = typename std::iterator_traits<OutputIt>::iterator_category,
         typename = typename std::enable_if<std::is_same<Tag, std::output_iterator_tag>::value>::type>
OutputIt test(char32_t v, OutputIt output)
{
    *output++ = v;
    return output;
}

int main()
{
    test('A', std::ostream_iterator<char>(std::cout));
}
