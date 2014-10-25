#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/algorithm.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_erasure/free.hpp>
#include <boost/type_erasure/any.hpp>

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
using namespace boost;
using namespace type_erasure;

/****************************************************************************/
using byte = unsigned char;

struct SerializatorWriter
{
    friend void serialize(SerializatorWriter&, byte &x)
    {
        void *p = &x;
        cout << "writing " << unsigned(x) << " from\t" << p << endl;
    }
};

struct SerializatorReader
{
    friend void serialize(SerializatorReader&, byte &result)
    {
        byte z = rand() % 10;
        result = z;
        void *p = &result;
        cout << "reading " << unsigned(z) << " to\t" << p << endl;
    }
};

template<typename Archive, typename T>
    typename boost::enable_if< fusion::traits::is_sequence<T> >::type
serialize(Archive &archive, T &xs)
{
    fusion::for_each(xs, [&](auto &x)
    {
        serialize(archive, x);
    });
}

BOOST_TYPE_ERASURE_FREE((has_serialize), serialize, 2)

template<typename ...Concepts>
using anything = any<mpl::vector<typeid_<>, Concepts...>, _self&>;

using any_serializer = anything<has_serialize<void(_self&, byte&)>>;
using any_serializable = anything<has_serialize<void(any_serializer&, _self&)>>;

/****************************************************************************/
BOOST_FUSION_DEFINE_STRUCT
(
    (), two_bytes,
    (byte, first)
    (byte, second)
)

BOOST_FUSION_DEFINE_STRUCT
(
    (), three_bytes,
    (two_bytes, first_two)
    (byte, third)
)

/****************************************************************************/
// DEMO:

void test_read(void *x)
{
    SerializatorReader reader;
    any_serializer ar = reader;
    serialize(ar, *static_cast<any_serializable*>(x));
}

void test_write(void *x)
{
    SerializatorWriter writer;
    any_serializer ar = writer;
    serialize(ar, *static_cast<any_serializable*>(x));
}

template<typename T>
void test(T &x)
{
    any_serializable s = x;

    test_read(&s);
    test_write(&s);

    cout << string(20, '_') << endl;;
}

int main()
{
    fusion::vector<three_bytes, byte, two_bytes> tuple1;
    test(tuple1);

    fusion::vector<fusion::vector<byte, three_bytes>, two_bytes, byte> tuple2;
    test(tuple2);
}
