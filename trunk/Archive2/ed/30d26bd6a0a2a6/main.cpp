#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/serialization.hpp>

#include <boost/serialization/vector.hpp>
#include <boost/spirit/include/karma.hpp>    // for serialization
#include <boost/spirit/include/qi.hpp>       // for deserialization
#include <boost/spirit/include/phoenix.hpp>  // for semantic actions
#include <boost/spirit/include/phoenix_container.hpp>

#include <sstream>
#include <iostream>
#include <iomanip> // debug output

namespace my_serialization_helpers {

    ////////////////////////////////////////////////////////////////////////////
    // This namespace serves as an extension point for your serialization; in
    // particular we choose endianness and representation of strings
    //
    // TODO add overloads as needed (signed integer types, binary floats,
    // containers of... etc)
    ////////////////////////////////////////////////////////////////////////////
    namespace qi    = boost::spirit::qi;
    namespace karma = boost::spirit::karma;
    
    // decide on the max supported string capacity:
#if 0
    using string_size_type = uint8_t;
    static const qi   ::byte_type string_size_type_par;
    static const karma::byte_type string_size_type_gen;
#elif 0
    using string_size_type = uint16_t;
    static const qi   ::little_word_type string_size_type_par;
    static const karma::little_word_type string_size_type_gen;
#elif 1
    using string_size_type = uint32_t;
    static const qi   ::little_dword_type string_size_type_par;
    static const karma::little_dword_type string_size_type_gen;
#elif 1
    using string_size_type = uint64_t;
    static const qi   ::little_qword_type string_size_type_par;
    static const karma::little_qword_type string_size_type_gen;
#endif
    
    ////////////////////////////////////////////////////////////////////////////
    // generators
    template <typename Out>
    bool do_generate(Out out, std::string const& data) {
        using boost::phoenix::size;
        using namespace karma;

        // if size doesn't exceed supported capacity, serialize the length
        static const rule<Out, std::string()> length_ = 
               eps(size(_val) <= std::numeric_limits<string_size_type>::max()) 
            << string_size_type_gen [ _1 = size(_val) ]
            ;

        // write length followed by raw bytes
        return generate(out, duplicate [ length_ << +byte_ ], data);
    }

    template <typename Out>
    bool do_generate(Out out, uint8_t const& data) {
        using namespace karma;
        return generate(out, byte_, data);
    }

    template <typename Out>
    bool do_generate(Out out, uint16_t const& data) {
        using namespace karma;
        return generate(out, little_word, data);
    }

    template <typename Out>
    bool do_generate(Out out, uint32_t const& data) {
        using namespace karma;
        return generate(out, little_dword, data);
    }

    ////////////////////////////////////////////////////////////////////////////
    // parsers
    template <typename It>
    bool do_parse(It& in, It last, std::string& data) {
        using namespace qi;
        using boost::phoenix::begin;
        using boost::phoenix::end;
        using boost::phoenix::assign;

        rule<It, std::string(), locals<string_size_type> > rule_ = 
              string_size_type_par       [ _a = _1 ]
            > raw[repeat(_a) [ byte_ ]]  [ assign(_val, begin(_1), end(_1)) ]
            ;

        return parse(in, last, rule_, data);
    }

    template <typename It>
    bool do_parse(It& in, It last, uint8_t& data) {
        using namespace qi;
        return parse(in, last, byte_, data);
    }

    template <typename It>
    bool do_parse(It& in, It last, uint16_t& data) {
        using namespace qi;
        return parse(in, last, little_word, data);
    }

    template <typename It>
    bool do_parse(It& in, It last, uint32_t& data) {
        using namespace qi;
        return parse(in, last, little_dword, data);
    }
}

struct StartPeerSessionRequest {
    void DoSaveTests();

    uint16_t    mProtocolVersion;
    uint16_t    mSessionFlags;
    uint16_t    mMaxResponseLength;
    std::string mMake;
    std::string mModel;
    std::string mSerialNumber;
    uint8_t     mTrackDelay;
    std::string mHeadUnitModel;
    std::string mCarModelYear;
    std::string mVin;
    uint16_t    mVehicleMileage;
    uint8_t     mShoutFormat;
    uint8_t     mNotificationInterval;

    template <typename Container>
    bool generate(Container& bytes) const {
        auto out = std::back_inserter(bytes);

        using my_serialization_helpers::do_generate;
        return do_generate(out, mProtocolVersion)
            && do_generate(out, mSessionFlags)
            && do_generate(out, mMaxResponseLength)
            && do_generate(out, mMake)
            && do_generate(out, mModel)
            && do_generate(out, mSerialNumber)
            && do_generate(out, mTrackDelay)
            && do_generate(out, mHeadUnitModel)
            && do_generate(out, mCarModelYear)
            && do_generate(out, mVin)
            && do_generate(out, mVehicleMileage)
            && do_generate(out, mShoutFormat)
            && do_generate(out, mNotificationInterval);
    }

    template <typename Container>
    bool parse(Container const& bytes) {
        using std::begin;
        using std::end;
        auto in = begin(bytes), last = end(bytes);

        using my_serialization_helpers::do_parse;
        return do_parse(in, last, mProtocolVersion)
            && do_parse(in, last, mSessionFlags)
            && do_parse(in, last, mMaxResponseLength)
            && do_parse(in, last, mMake)
            && do_parse(in, last, mModel)
            && do_parse(in, last, mSerialNumber)
            && do_parse(in, last, mTrackDelay)
            && do_parse(in, last, mHeadUnitModel)
            && do_parse(in, last, mCarModelYear)
            && do_parse(in, last, mVin)
            && do_parse(in, last, mVehicleMileage)
            && do_parse(in, last, mShoutFormat)
            && do_parse(in, last, mNotificationInterval);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Boost Serialization adaptation
    BOOST_SERIALIZATION_SPLIT_MEMBER()

    template <typename Archive> void save(Archive &ar, unsigned) const { std::vector<uint8_t> binary;
        if (generate(binary)) {
            ar & binary;
        } else {
            throw "serialization failed"; // TODO FIXME exception type
        }
    }

    template <typename Archive> void load(Archive &ar, unsigned) {
        std::vector<uint8_t> binary;
        ar & binary; 
        if (!parse(binary)) {
            throw "deserialization failed"; // TODO FIXME exception type
        }
    }
};

StartPeerSessionRequest create() {
    return StartPeerSessionRequest {
        1 * 10000 + 14 * 100 + 4, // 2 bytes
        1,                        // 2 bytes
        0,                        // 2 bytes
        "MyMake",                 // 6 bytes + length
        "MyModel",                // 7 bytes + length
        "10000",                  // 5 bytes + length
        0,                        // 1 byte
        "Headunit",               // 8  bytes + length
        "2014",                   // 4  bytes + length
        "1234567980",             // 10 bytes + length
        1000,                     // 2 byte
        3,                        // 1 byte
        1,                        // 1 byte
    };
}

void StartPeerSessionRequest::DoSaveTests() {
    std::ostringstream serlreq;

    boost::archive::binary_oarchive oa(serlreq, boost::archive::no_header);
    oa << (*this);
    std::string bytes = serlreq.str();
    std::cout << "\nbinary_oarchive :" << std::dec << bytes.length() << "\n";
    for (auto ch : bytes)
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>((uint8_t)ch) << " ";
    std::cout << std::dec << "\n";
}

#include <cassert>

int main() {
    StartPeerSessionRequest req = create();

    std::vector<uint8_t> bytes;
    if (req.generate(bytes))
    {
        std::cout << "\nSpirit karma bytes :" << std::dec << bytes.size() << "\n";

        StartPeerSessionRequest clone;
        if (clone.parse(bytes))
        {
            std::vector<uint8_t> roundtrip;
            assert(clone.generate(roundtrip) && (roundtrip==bytes));
        } else
        {
            std::cout << "Spirit roundtrip deserialization failed\n";
        }
    } else
    {
        std::cout << "Spirit serialization failed\n";
    }

    // your "old" boost serialization code, reusing the Spirit formatting ^
    req.DoSaveTests();
}
