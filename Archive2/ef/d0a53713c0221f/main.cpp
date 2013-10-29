/* compile with g++ 4.4.6: g++ -I boost_1_35_0 test6.cpp (g++ 4.5.1 boost 1.47.0) */
#include <typeinfo>
#include <string>
#include <boost/fusion/include/sequence.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits.hpp> // is_array, is_class, remove_bounds
#include <boost/lexical_cast.hpp>
using namespace boost::fusion;

#define DEMANGLING

#ifdef DEMANGLING
#   include <cxxabi.h>
#   include <stdlib.h>

    namespace mangling {
        template <typename T> std::string nameofType(const T& v) {
            int     status;
            char   *realname = abi::__cxa_demangle(typeid(v).name(), 0, 0, &status);
            std::string name(realname? realname : "????");
            free(realname);

            return name;
        }
    }
#else
    namespace mangling {
        template <typename T> std::string nameofType(const T& v) {
            return std::string("typeid(") + typeid(v).name() + ")";
        }
    }
#endif

namespace FusionDumping 
{
    // everything except the `dump(std::ostream&, T const&)` function is an implementation detail
    using mangling::nameofType;

    template <typename T2> struct Dec_s;

    template <typename S, typename N> struct DecImplSeqItr_s {
        typedef typename boost::fusion::result_of::value_at<S, N>::type current_t;
        typedef typename boost::mpl::next<N>::type next_t;
        typedef boost::fusion::extension::struct_member_name<S, N::value> name_t;
        static inline std::ostream& decode(std::ostream& os, S const& s) {
            os << "field " << name_t::call() << " ";
            Dec_s<current_t>::decode(os, boost::fusion::at<N>(s));
            return DecImplSeqItr_s<S, next_t>::decode(os, s);
        }
    };

    template <typename S>
    struct DecImplSeqItr_s<S, typename boost::fusion::result_of::size<S>::type > {
        static inline std::ostream& decode(std::ostream& os, S const& s) { return os; }
    };

    template <typename S>
    struct DecImplSeqStart_s:DecImplSeqItr_s<S, boost::mpl::int_<0> > {};

    template <typename S> struct DecImplSeq_s {
    typedef DecImplSeq_s<S> type;
    static std::ostream& decode(std::ostream& os, S const& s) {
        os << "STRUCT " << nameofType(s) << "\n";
        DecImplSeqStart_s<S>::decode(os, s);
        return os << "ENDSTRUCT\n";
    };
    };

    template <typename T2> struct DecImplArray_s {
    typedef DecImplArray_s<T2> type;
    typedef typename boost::remove_bounds<T2>::type slice_t;
    static const size_t size = sizeof(T2) / sizeof(slice_t);
    static inline std::ostream& decode(std::ostream& os, T2 const& t) {
        os << "ARRAY [\n";
        for(size_t idx=0; idx<size; idx++) { Dec_s<slice_t>::decode(os, t[idx]); }
        return os << "]\n";
    }
    };

    template <typename T2> struct DecImplVoid_s {
    typedef DecImplVoid_s<T2> type;
    static std::ostream& decode(std::ostream& os, T2 const& t) { 
        return os << nameofType(t) << ": " << boost::lexical_cast<std::string>(t) << "\n";
    };
    };

    template <typename T2> struct DecCalc_s {
    typedef 
        typename boost::mpl::eval_if< traits::is_sequence<T2>, DecImplSeq_s<T2>, 
        typename boost::mpl::eval_if< boost::is_array<T2>, 
                                    boost::mpl::identity< DecImplArray_s<T2> >,
        DecImplVoid_s<T2>   > >
    ::type type;
    };

    template <typename T2> struct Dec_s : public DecCalc_s<T2>::type { };

    template <typename Data>
    struct Dumper
    {
        Dumper(Data const& data) : data(data) {}
        friend std::ostream& operator<<(std::ostream& os, const Dumper& manip) {
            return Dec_s<Data>::decode(os, manip.data);
        }
    private:
        Data const& data;
    };

    template <typename Data>
        Dumper<Data> dump(Data const& data) { return { data }; }
}

struct A {
  int a;
  typedef std::string strings[5];
  strings b;
};

BOOST_FUSION_ADAPT_STRUCT(A, (int, a)(A::strings, b))

int main() {
    using FusionDumping::dump;
    A f = { 42, { "The End Of The Universe", "Thanks For All The Fish", "Fwoop fwoop fwoop", "Don't Panic" } };
    std::cout << dump(f) << "\n";
}
