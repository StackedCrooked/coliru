#include <boost/archive/text_oarchive.hpp>

typedef uint32_t WORD;

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME;

namespace boost { namespace serialization {
    template<typename Archive>
        void serialize(Archive& ar, SYSTEMTIME& st, const unsigned int version) {
            ar & st.wYear;
            ar & st.wMonth;
            ar & st.wDayOfWeek;
            ar & st.wDay;
            ar & st.wHour;
            ar & st.wMinute;
            ar & st.wSecond;
            ar & st.wMilliseconds;
        }
} }

int main()
{
    boost::archive::text_oarchive oa(std::cout);
    SYSTEMTIME d { 1,2,3,4,5,6,7,8 };
    oa << d;
}

