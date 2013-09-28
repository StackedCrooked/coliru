#include <vector>
#include <unordered_map>
#include <boost/variant.hpp>

namespace libdocplus {
    typedef bool Boolean;
    typedef int Integer;
    typedef double Real;
    typedef std::vector<unsigned char> ByteBuffer;
    typedef ByteBuffer String;
    typedef ByteBuffer Name;
    typedef ByteBuffer Stream;
    class Null {};

    class DictionaryWrapper;
    class ArrayWrapper {
        public:
            typedef boost::variant<Boolean, Integer, Real, String, Name, Stream, Null, boost::recursive_wrapper<ArrayWrapper>, boost::recursive_wrapper<DictionaryWrapper>> ScalarType;
            std::vector<ScalarType> Array;
    };

    class DictionaryWrapper {
        public:
            typedef boost::variant<Boolean, Integer, Real, String, Name, Stream, Null, boost::recursive_wrapper<DictionaryWrapper>, boost::recursive_wrapper<ArrayWrapper>> ScalarType;
            std::unordered_map<ScalarType, ScalarType> Dictionary;
    };

    typedef ArrayWrapper Array;
    typedef DictionaryWrapper Dictionary;
    typedef boost::variant<Boolean, Integer, Real, String, Name, Stream, Null, Array, Dictionary> Object;

    class PDFStreamParser {
    };
}

#include <iostream>

int main() {
    using namespace libdocplus;
    Object b = true;
    Object i = 1;
    Object r = 2.0;
    Object m = DictionaryWrapper();
    auto d = boost::get<DictionaryWrapper>(m);
    d.Dictionary[1] = 2;
}