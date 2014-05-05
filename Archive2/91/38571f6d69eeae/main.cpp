#define LIVE_DANGEROUSLY
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/integer.hpp>
#include <sstream>

namespace detail
{
    using namespace boost::spirit;
    // meta programming helpers
    template <int bits, typename endianness = struct big> struct int_traits;

    template <typename endianness> struct int_traits<8, endianness/*ignored*/> { 
        typedef uint8_t                  type;
        typedef qi::byte_type            parser;
        typedef karma::byte_type         generator;
    };

    template <> struct int_traits<16, struct big> {
        typedef uint16_t                 type;
        typedef qi::big_word_type        parser;
        typedef karma::big_word_type     generator;
    };

    template <> struct int_traits<32, struct big> {
        typedef uint32_t                 type;
        typedef qi::big_dword_type       parser;
        typedef karma::big_dword_type    generator;
    };

    template <> struct int_traits<64, struct big> {
        typedef uint64_t                 type;
        typedef qi::big_qword_type       parser;
        typedef karma::big_qword_type    generator;
    };

    template <> struct int_traits<16, struct little> {
        typedef uint16_t                 type;
        typedef qi::little_word_type     parser;
        typedef karma::little_word_type  generator;
    };

    template <> struct int_traits<32, struct little> {
        typedef uint32_t                 type;
        typedef qi::little_dword_type    parser;
        typedef karma::little_dword_type generator;
    };

    template <> struct int_traits<64, struct little> {
        typedef uint64_t                 type;
        typedef qi::little_qword_type    parser;
        typedef karma::little_qword_type generator;
    };
}

struct Message
{
    friend std::ostream& operator <<(std::ostream& os, Message const& msg) {
        msg.buffer.seekg(0, std::ios_base::beg);
        return os << msg.buffer.rdbuf();
    }

    friend std::istream& operator >>(std::istream& is, Message const& msg) {
        msg.buffer.clear(); // this will overwrite our header
        msg.buffer.str("");
        return is >> msg.buffer.rdbuf();
    }

    template <typename Int>
    friend typename boost::enable_if<typename boost::is_integral<Int>::type, Message&>::type
        operator <<(Message& msg, Int v)
        {
            msg.buffer.seekp(0, std::ios_base::end);
            msg.append_int(v);
            return msg;
        }

    template <typename Int, size_t N>
    friend typename boost::enable_if<typename boost::is_integral<Int>::type, Message&>::type
        operator <<(Message& msg, Int const (&v)[N])
        {
            msg.buffer.seekp(0, std::ios_base::end);
            msg.append_int(v);
            return msg;
        }

    template <typename Int>
    friend typename boost::enable_if<typename boost::is_integral<Int>::type, Message&>::type
        operator >>(Message& msg, Int& v)
        {
            msg.extract_int(v);
            return msg;
        }

    template <typename Int, size_t N>
    friend typename boost::enable_if<typename boost::is_integral<Int>::type, Message&>::type
        operator >>(Message& msg, Int (&v)[N])
        {
            msg.extract_ints(v);
            return msg;
        }

    Message() : buffer { "\xee\x33" }
    {
        buffer.unsetf(std::ios::skipws);
    }
    
  private:
    std::stringstream mutable buffer;

    template <typename Int, int bits=std::numeric_limits<Int>::digits + std::numeric_limits<Int>::is_signed>
    void append_int(Int v)
    {
        namespace karma = boost::spirit::karma;
        static const typename detail::int_traits<bits>::generator gen {};
        karma::generate(std::ostreambuf_iterator<char>(buffer), gen, static_cast<typename detail::int_traits<bits>::type>(v));
    }

    template <typename Int, int bits=std::numeric_limits<Int>::digits + std::numeric_limits<Int>::is_signed>
    void extract_int(Int& v)
    {
        namespace qi = boost::spirit::qi;
        static const typename detail::int_traits<bits>::parser p {};
        boost::spirit::istream_iterator f(buffer), l;
        qi::parse(f, l, p, v);
    }

    template <typename Int, size_t N, int bits=std::numeric_limits<Int>::digits + std::numeric_limits<Int>::is_signed>
    void append_int(Int const(&v)[N])
    {
#ifdef LIVE_DANGEROUSLY // optimize, but implementation defined cast
        namespace karma = boost::spirit::karma;
        static const typename detail::int_traits<bits>::generator gen {};
        auto data = reinterpret_cast<typename detail::int_traits<bits>::type const*>(&v[0]);
        karma::generate(std::ostreambuf_iterator<char>(buffer), +gen, boost::make_iterator_range(data,data+N));
#else
        for(auto& i:v)
            append_int(i);
#endif
    }

    template <typename Int, size_t N, int bits=std::numeric_limits<Int>::digits + std::numeric_limits<Int>::is_signed>
    void extract_ints(Int (&v)[N])
    {
        for(auto& i:v)
            extract_int(i);
    }
};

std::string serialize_message()
{
    uint8_t  ipv4[4] = { 127, 0, 0, 1 };
    uint64_t ipv6[2] = { 0xdeadbeef00004b1d, 0xcafed00dcafebabe };
    uint8_t  alg     = 2;

    Message msg;
    msg << ipv4 << ipv6 << alg;

    // stringyfy
    std::stringstream ss;
    ss << msg;
    return ss.str();
}

int main()
{
    std::string const rep = serialize_message();
    std::cout << rep << std::flush; // for demo (view in hex)

    // reconstruct
    Message roundtrip;
    std::istringstream(rep) >> roundtrip;

    uint8_t  ipv4[4] = { 0 };
    uint64_t ipv6[2] = { 0 };
    uint8_t  alg     = 0;
    roundtrip >> ipv4 >> ipv6 >> alg;

    assert(rep == boost::lexical_cast<std::string>(roundtrip));
}
