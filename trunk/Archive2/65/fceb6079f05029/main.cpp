#include <boost/operators.hpp>
#include <boost/preprocessor.hpp>


#define STRONG_TYPEDEF(T, Name) \
    struct Name : boost::operators<Name> \
    { \
        Name() : t() {} \
        explicit Name(const T & t_) : t(t_) {} \
        operator const T&() const { return t; } \
        operator T&() { return t; } \
        const T& get() const { return t; } \
        T& get() { return t; } \
        Name& operator=(const T& rhs_t) { t = rhs_t; return *this; } \
        Name& operator=(const Name& rhs) { t = rhs.t; return *this; } \
        friend bool operator<(const Name& lhs, const Name& rhs) { return lhs.t < rhs.t; } \
        friend bool operator==(const Name& lhs, const Name& rhs) { return lhs.t == rhs.t; } \
        T t; \
    }

#define STRONG_TYPEDEF_(type_and_name) STRONG_TYPEDEF(BOOST_PP_TUPLE_ELEM(2, 0, type_and_name), BOOST_PP_TUPLE_ELEM(2, 1, type_and_name));

#define DEFINE_RECORD_2(type_and_name, ...) STRONG_TYPEDEF_(type_and_name) STRONG_TYPEDEF_(__VA_ARGS__)
#define DEFINE_RECORD_3(type_and_name, ...) STRONG_TYPEDEF_(type_and_name) DEFINE_RECORD_2(__VA_ARGS__)
#define DEFINE_RECORD_4(type_and_name, ...) STRONG_TYPEDEF_(type_and_name) DEFINE_RECORD_3(__VA_ARGS__)
#define DEFINE_RECORD_5(type_and_name, ...) STRONG_TYPEDEF_(type_and_name) DEFINE_RECORD_4(__VA_ARGS__)
#define DEFINE_RECORD_6(type_and_name, ...) STRONG_TYPEDEF_(type_and_name) DEFINE_RECORD_5(__VA_ARGS__)
#define DEFINE_RECORD_7(type_and_name, ...) STRONG_TYPEDEF_(type_and_name) DEFINE_RECORD_6(__VA_ARGS__)
#define DEFINE_RECORD_8(type_and_name, ...) STRONG_TYPEDEF_(type_and_name) DEFINE_RECORD_7(__VA_ARGS__)

#define DEFINE_RECORD(Name, ...) \
    struct Name; \
    BOOST_PP_CAT(DEFINE_RECORD_, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)


DEFINE_RECORD(Stats2,
    (int64_t, ByteCount),
    (int64_t, FrameCount),
    (int64_t, TimeFirstFrame),
    (int64_t, TimeLastFrame),
    (int64_t, TimeSnapshot),
    (int64_t, SnapshotType),
    (int64_t, ExtraStuff)
)

int main() { FrameCount frameCount{1}; return frameCount.get(); }
