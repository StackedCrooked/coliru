#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <iostream>
#include <sstream>

template <class cha_type, class iterator_type>
struct my_source {
    typedef cha_type char_type;
    typedef boost::iostreams::source_tag category;

    iterator_type& it;
    iterator_type end;

    my_source(iterator_type& it, iterator_type end = {}) : it(it), end(end) 
    { }

    std::streamsize read(char* s, std::streamsize n) {
        std::streamsize result = 0;
        while ((it!=end) && n--) {
            ++result;
            *s++ = *it++;
        }
        return result;
    }
};

int main() {       
    std::string const rawdata {'x', '\234', '\313', 'H', '\315', '\311', '\311', 'W', '(', '\317', '/', '\312', 'I', '\341', '\002', '\0', '\036', 'r', '\004', 'g' };
    std::istringstream iss(rawdata, std::ios::binary);

    auto start = std::istreambuf_iterator<char>(iss);
    my_source<char, decltype(start)> data(start);

    boost::iostreams::filtering_istreambuf def;
    def.push(boost::iostreams::zlib_decompressor());
    def.push(data);

    boost::iostreams::copy(def, std::cout);
}
