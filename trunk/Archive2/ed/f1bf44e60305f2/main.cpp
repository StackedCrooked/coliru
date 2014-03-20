#include <cstring>
#include <boost/cstdint.hpp>

class alignas(boost::uint64_t) header {
    const boost::uint8_t version;
    const boost::uint8_t type;

    const union {
        boost::uint16_t requestId;
        struct {
            boost::uint8_t requestIdB1;
            boost::uint8_t requestIdB0;
        };
    };

    const union {
        boost::uint16_t contentLength;
        struct {
            boost::uint8_t contentLengthB1;
            boost::uint8_t contentLengthB0;
        };
    };
    const boost::uint8_t paddingLength;
    const boost::uint8_t reserved;

    header(const char* header);
};

header::header(const char* __restrict__ header) :
  version(header[0]), type(header[1]),
  requestIdB1(header[2]), requestIdB0(header[3]),
  contentLengthB1(header[4]), contentLengthB0(header[5]),
  paddingLength(header[6]), reserved(header[7]) {}

template <typename T>
T from_bytes(const char* __restrict__ bytes) {
  T result;
  // static_assert(std::is_trivially_copyable<T>::value, "Jabberwocky is killing user.");
  std::memcpy(&result, bytes, sizeof(result));
  return result;
}

boost::uint64_t foo(const char* bytes) {
  return from_bytes<boost::uint64_t>(bytes);
}
