#include <boost/preprocessor.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>  
#include <boost/shared_ptr.hpp>

#define DEFINE_STRUCT(name, fields)          \
    DEFINE_STRUCT_I(name,                    \
        BOOST_PP_CAT(DEFINE_STRUCT_X fields, 0))

#define DEFINE_STRUCT_X(x, y) ((x, y)) DEFINE_STRUCT_Y
#define DEFINE_STRUCT_Y(x, y) ((x, y)) DEFINE_STRUCT_X
#define DEFINE_STRUCT_X0
#define DEFINE_STRUCT_Y0

#define DEFINE_STRUCT_I(name, fields)        \
    class name                               \
    {                                        \
        BOOST_PP_SEQ_FOR_EACH_I              \
            (DEFINE_STRUCT_FIELD, _, fields) \
    public:                                  \
        name() {}                            \
    public:                                  \
    template <class T, int> friend struct boost::fusion::extension::access::struct_member;\
   };                                       \
    BOOST_FUSION_ADAPT_STRUCT_I_PTR(name, fields)\
    struct name##_table : public table_container<name>\
    {\
    };

#define DEFINE_STRUCT_FIELD(r, _, i, xy)     \
    BOOST_PP_TUPLE_ELEM(2, 0, xy)            \
        *BOOST_PP_TUPLE_ELEM(2, 1, xy);

#define BOOST_FUSION_ADAPT_STRUCT_I_PTR(name, seq)                              \
    namespace boost { namespace fusion { namespace traits                       \
    {                                                                           \
        template <>                                                             \
        struct tag_of<name>                                                     \
        {                                                                       \
            typedef struct_tag type;                                            \
        };                                                                      \
    }}}                                                                         \
    namespace boost { namespace fusion { namespace extension                    \
    {                                                                           \
        template <>                                                             \
        struct struct_size<name> : mpl::int_<BOOST_PP_SEQ_SIZE(seq)> {};        \
        BOOST_PP_SEQ_FOR_EACH_I(BOOST_FUSION_ADAPT_STRUCT_C_PTR, name, seq)     \
    }}}                                                                         \

#define BOOST_FUSION_ADAPT_STRUCT_C_PTR(r, name, i, xy)                         \
    template <>                                                                 \
    struct access::struct_member<name, i>                                       \
    {                                                                           \
        typedef BOOST_PP_TUPLE_ELEM(2, 0, xy)* type;                            \
        static type& call(name& struct_)                                        \
        {                                                                       \
            return struct_.BOOST_PP_TUPLE_ELEM(2, 1, xy);                       \
        };                                                                      \
    };                                                                          \

template<class T>
struct table_container
{
    T val;
};



DEFINE_STRUCT(new_buildin,
(int, col1)
(char, col2))



int main()
{
    new_buildin_table b;
    boost::fusion::at<boost::mpl::int_<1>>(b.val);
    return 0;
}