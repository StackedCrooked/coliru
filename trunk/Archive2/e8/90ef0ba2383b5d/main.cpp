#include "boost/preprocessor.hpp"


#define XXX_PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N

#define XXX_PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0 

#define XXX_PP_NARG_(...) \
         XXX_PP_ARG_N(__VA_ARGS__)

#define XXX_PP_NARG(...) \
         XXX_PP_NARG_(__VA_ARGS__,XXX_PP_RSEQ_N())

#define XXX_TUPLE_SIZE_INTERNAL(TUPLE) XXX_PP_NARG TUPLE

#define XXX_TUPLE_CHOICE(i) \
BOOST_PP_APPLY( \
BOOST_PP_TUPLE_ELEM( \
25, i, (\
(0), (1), (2), (3) , (4) , (5) , (6) , (7) , (8) , (9) , (10) , (11)            \
, (12) , (13) , (14) , (15) , (16) , (17) , (18) , (19) , (20) , (21)           \
, (22) , (23) , (24)    \
 ) \
) \
)


#define BOOST_PP_BOOL_00 BOOST_PP_BOOL_0
#define BOOST_PP_BOOL_01 BOOST_PP_BOOL_1
#define BOOST_PP_BOOL_02 BOOST_PP_BOOL_2
#define BOOST_PP_BOOL_03 BOOST_PP_BOOL_3
#define BOOST_PP_BOOL_04 BOOST_PP_BOOL_4
#define BOOST_PP_BOOL_05 BOOST_PP_BOOL_5
#define BOOST_PP_BOOL_06 BOOST_PP_BOOL_6
#define BOOST_PP_BOOL_07 BOOST_PP_BOOL_7
#define BOOST_PP_BOOL_08 BOOST_PP_BOOL_8
#define BOOST_PP_BOOL_09 BOOST_PP_BOOL_9
#define BOOST_PP_BOOL_010 BOOST_PP_BOOL_10
#define BOOST_PP_BOOL_011 BOOST_PP_BOOL_11
#define BOOST_PP_BOOL_012 BOOST_PP_BOOL_12
#define BOOST_PP_BOOL_013 BOOST_PP_BOOL_13
#define BOOST_PP_BOOL_014 BOOST_PP_BOOL_14
#define BOOST_PP_BOOL_015 BOOST_PP_BOOL_15
#define BOOST_PP_BOOL_016 BOOST_PP_BOOL_16
#define BOOST_PP_BOOL_017 BOOST_PP_BOOL_17
#define BOOST_PP_BOOL_018 BOOST_PP_BOOL_18
#define BOOST_PP_BOOL_019 BOOST_PP_BOOL_19
#define BOOST_PP_BOOL_020 BOOST_PP_BOOL_20
#define BOOST_PP_BOOL_021 BOOST_PP_BOOL_21
#define BOOST_PP_BOOL_022 BOOST_PP_BOOL_22
#define BOOST_PP_BOOL_023 BOOST_PP_BOOL_23
#define BOOST_PP_BOOL_024 BOOST_PP_BOOL_24
#define BOOST_PP_BOOL_025 BOOST_PP_BOOL_25
#define BOOST_PP_BOOL_026 BOOST_PP_BOOL_26
#define BOOST_PP_BOOL_027 BOOST_PP_BOOL_27
#define BOOST_PP_BOOL_028 BOOST_PP_BOOL_28
#define BOOST_PP_BOOL_029 BOOST_PP_BOOL_29
#define BOOST_PP_BOOL_030 BOOST_PP_BOOL_30
#define BOOST_PP_BOOL_031 BOOST_PP_BOOL_31
#define BOOST_PP_BOOL_032 BOOST_PP_BOOL_32
#define BOOST_PP_BOOL_033 BOOST_PP_BOOL_33
#define BOOST_PP_BOOL_034 BOOST_PP_BOOL_34
#define BOOST_PP_BOOL_035 BOOST_PP_BOOL_35
#define BOOST_PP_BOOL_036 BOOST_PP_BOOL_36
#define BOOST_PP_BOOL_037 BOOST_PP_BOOL_37
#define BOOST_PP_BOOL_038 BOOST_PP_BOOL_38
#define BOOST_PP_BOOL_039 BOOST_PP_BOOL_39
#define BOOST_PP_BOOL_040 BOOST_PP_BOOL_40
#define BOOST_PP_BOOL_041 BOOST_PP_BOOL_41
#define BOOST_PP_BOOL_042 BOOST_PP_BOOL_42
#define BOOST_PP_BOOL_043 BOOST_PP_BOOL_43
#define BOOST_PP_BOOL_044 BOOST_PP_BOOL_44
#define BOOST_PP_BOOL_045 BOOST_PP_BOOL_45
#define BOOST_PP_BOOL_046 BOOST_PP_BOOL_46
#define BOOST_PP_BOOL_047 BOOST_PP_BOOL_47
#define BOOST_PP_BOOL_048 BOOST_PP_BOOL_48
#define BOOST_PP_BOOL_049 BOOST_PP_BOOL_49
#define BOOST_PP_BOOL_050 BOOST_PP_BOOL_50
#define BOOST_PP_BOOL_051 BOOST_PP_BOOL_51
#define BOOST_PP_BOOL_052 BOOST_PP_BOOL_52
#define BOOST_PP_BOOL_053 BOOST_PP_BOOL_53
#define BOOST_PP_BOOL_054 BOOST_PP_BOOL_54
#define BOOST_PP_BOOL_055 BOOST_PP_BOOL_55
#define BOOST_PP_BOOL_056 BOOST_PP_BOOL_56
#define BOOST_PP_BOOL_057 BOOST_PP_BOOL_57
#define BOOST_PP_BOOL_058 BOOST_PP_BOOL_58
#define BOOST_PP_BOOL_059 BOOST_PP_BOOL_59
#define BOOST_PP_BOOL_060 BOOST_PP_BOOL_60
#define BOOST_PP_BOOL_061 BOOST_PP_BOOL_61
#define BOOST_PP_BOOL_062 BOOST_PP_BOOL_62
#define BOOST_PP_BOOL_063 BOOST_PP_BOOL_63


#define BOOST_PP_DEC_00 BOOST_PP_DEC_0
#define BOOST_PP_DEC_01 BOOST_PP_DEC_1
#define BOOST_PP_DEC_02 BOOST_PP_DEC_2
#define BOOST_PP_DEC_03 BOOST_PP_DEC_3
#define BOOST_PP_DEC_04 BOOST_PP_DEC_4
#define BOOST_PP_DEC_05 BOOST_PP_DEC_5
#define BOOST_PP_DEC_06 BOOST_PP_DEC_6
#define BOOST_PP_DEC_07 BOOST_PP_DEC_7
#define BOOST_PP_DEC_08 BOOST_PP_DEC_8
#define BOOST_PP_DEC_09 BOOST_PP_DEC_9
#define BOOST_PP_DEC_010 BOOST_PP_DEC_10
#define BOOST_PP_DEC_011 BOOST_PP_DEC_11
#define BOOST_PP_DEC_012 BOOST_PP_DEC_12
#define BOOST_PP_DEC_013 BOOST_PP_DEC_13
#define BOOST_PP_DEC_014 BOOST_PP_DEC_14
#define BOOST_PP_DEC_015 BOOST_PP_DEC_15
#define BOOST_PP_DEC_016 BOOST_PP_DEC_16
#define BOOST_PP_DEC_017 BOOST_PP_DEC_17
#define BOOST_PP_DEC_018 BOOST_PP_DEC_18
#define BOOST_PP_DEC_019 BOOST_PP_DEC_19
#define BOOST_PP_DEC_020 BOOST_PP_DEC_20
#define BOOST_PP_DEC_021 BOOST_PP_DEC_21
#define BOOST_PP_DEC_022 BOOST_PP_DEC_22
#define BOOST_PP_DEC_023 BOOST_PP_DEC_23
#define BOOST_PP_DEC_024 BOOST_PP_DEC_24
#define BOOST_PP_DEC_025 BOOST_PP_DEC_25
#define BOOST_PP_DEC_026 BOOST_PP_DEC_26
#define BOOST_PP_DEC_027 BOOST_PP_DEC_27
#define BOOST_PP_DEC_028 BOOST_PP_DEC_28
#define BOOST_PP_DEC_029 BOOST_PP_DEC_29
#define BOOST_PP_DEC_030 BOOST_PP_DEC_30
#define BOOST_PP_DEC_031 BOOST_PP_DEC_31
#define BOOST_PP_DEC_032 BOOST_PP_DEC_32
#define BOOST_PP_DEC_033 BOOST_PP_DEC_33
#define BOOST_PP_DEC_034 BOOST_PP_DEC_34
#define BOOST_PP_DEC_035 BOOST_PP_DEC_35
#define BOOST_PP_DEC_036 BOOST_PP_DEC_36
#define BOOST_PP_DEC_037 BOOST_PP_DEC_37
#define BOOST_PP_DEC_038 BOOST_PP_DEC_38
#define BOOST_PP_DEC_039 BOOST_PP_DEC_39
#define BOOST_PP_DEC_040 BOOST_PP_DEC_40
#define BOOST_PP_DEC_041 BOOST_PP_DEC_41
#define BOOST_PP_DEC_042 BOOST_PP_DEC_42
#define BOOST_PP_DEC_043 BOOST_PP_DEC_43
#define BOOST_PP_DEC_044 BOOST_PP_DEC_44
#define BOOST_PP_DEC_045 BOOST_PP_DEC_45
#define BOOST_PP_DEC_046 BOOST_PP_DEC_46
#define BOOST_PP_DEC_047 BOOST_PP_DEC_47
#define BOOST_PP_DEC_048 BOOST_PP_DEC_48
#define BOOST_PP_DEC_049 BOOST_PP_DEC_49
#define BOOST_PP_DEC_050 BOOST_PP_DEC_50
#define BOOST_PP_DEC_051 BOOST_PP_DEC_51
#define BOOST_PP_DEC_052 BOOST_PP_DEC_52
#define BOOST_PP_DEC_053 BOOST_PP_DEC_53
#define BOOST_PP_DEC_054 BOOST_PP_DEC_54
#define BOOST_PP_DEC_055 BOOST_PP_DEC_55
#define BOOST_PP_DEC_056 BOOST_PP_DEC_56
#define BOOST_PP_DEC_057 BOOST_PP_DEC_57
#define BOOST_PP_DEC_058 BOOST_PP_DEC_58
#define BOOST_PP_DEC_059 BOOST_PP_DEC_59
#define BOOST_PP_DEC_060 BOOST_PP_DEC_60
#define BOOST_PP_DEC_061 BOOST_PP_DEC_61
#define BOOST_PP_DEC_062 BOOST_PP_DEC_62
#define BOOST_PP_DEC_063 BOOST_PP_DEC_63


#define XXX_TO_NUMx(x) 0 ## x
#define XXX_TO_NUM(x) BOOST_PP_ADD(0,XXX_TO_NUMx(x))


#define XXX_STRINGIZEX(x) # x
#define XXX_VSTRINGIZE_SINGLE(a,b,x) XXX_STRINGIZE(x)
#define XXX_VSTRINGIZE_TUPLE(tpl) XXX_TUPLE_FOR_EACH(XXX_VSTRINGIZE_SINGLE,,tpl)






#define XXX_TUPLE_SIZE(TUPLE) XXX_TO_NUM(XXX_TUPLE_CHOICE(XXX_TUPLE_SIZE_INTERNAL(TUPLE)))




#define XXX_TUPLE_FOR_EACH(MACRO,DATA,TUPLE) BOOST_PP_LIST_FOR_EACH(MACRO,DATA,BOOST_PP_TUPLE_TO_LIST(XXX_TUPLE_SIZE(TUPLE),TUPLE))

#define XXX_STRINGIZE(x) XXX_STRINGIZEX(x)

#define XXX_VSTRINGIZE(...) XXX_VSTRINGIZE_TUPLE((__VA_ARGS__))

#define XXX_CAST_TO_VOID_ELEMENT(r,data,elem) (void)(elem);
#define XXX_CAST_TO_VOID_INTERNAL(TUPLE)                                                                                \
        XXX_TUPLE_FOR_EACH(XXX_CAST_TO_VOID_ELEMENT,,TUPLE)

#define XXX_CAST_TO_VOID(...) XXX_CAST_TO_VOID_INTERNAL((__VA_ARGS__))



#define XXX_ENUM_EXTRACT_SP(en) BOOST_PP_TUPLE_ELEM(XXX_TUPLE_SIZE(en),0,en) = BOOST_PP_TUPLE_ELEM(XXX_TUPLE_SIZE(en),1,en)
#define XXX_ENUM_ELEMENT(r,data,elem) BOOST_PP_IF( XXX_TUPLE_SIZE(elem), XXX_ENUM_EXTRACT_SP(elem), elem) ,
#define XXX_ENUM_EXTRACT_ELEMENT(en) BOOST_PP_TUPLE_ELEM(XXX_TUPLE_SIZE(en),0,en)
#define XXX_ENUM_CASE_ELEMENT(en) BOOST_PP_IF( XXX_TUPLE_SIZE(en), XXX_ENUM_EXTRACT_ELEMENT(en), en )

#define XXX_ENUM_CASE(r,data,elem) case data :: XXX_ENUM_CASE_ELEMENT(elem) : return #data "::" XXX_STRINGIZE(XXX_ENUM_CASE_ELEMENT(elem));

#define XXX_ENUM_IFELSE(r,data,elem) else if( en == data :: XXX_ENUM_CASE_ELEMENT(elem)) { return #data "::" XXX_STRINGIZE(XXX_ENUM_CASE_ELEMENT(elem)); }
#define XXX_ENUM_CASTLIST(r,data,elem) { XXX_STRINGIZE(XXX_ENUM_CASE_ELEMENT(elem)), data :: XXX_ENUM_CASE_ELEMENT(elem) },
#define XXX_ENUM_QUALIFIED_CASTLIST(r,data,elem) { #data "::" XXX_STRINGIZE(XXX_ENUM_CASE_ELEMENT(elem)), data :: XXX_ENUM_CASE_ELEMENT(elem) },

#define XXX_ENUM_INTERNAL(TYPE,NAME,TUPLE)                                                              \
enum TYPE                                                                                                                               \
{                                                                                                                                               \
        XXX_TUPLE_FOR_EACH(XXX_ENUM_ELEMENT,,TUPLE)                                                     \
        BOOST_PP_CAT(last_enum_,NAME)                                                                           \
};                                                                                                                                              \
                                                                                                                                                \
inline                                                                                                                                  \
const char* to_string( NAME en )                                                                                \
{                                                                                                                                               \
        if(false)                                                                                                                       \
        {                                                                                                                                       \
        }                                                                                                                                       \
        XXX_TUPLE_FOR_EACH(XXX_ENUM_IFELSE,NAME,TUPLE)                                          \
        else if( en == NAME :: BOOST_PP_CAT(last_enum_,NAME) )                          \
        {                                                                                                                                       \
                return XXX_VSTRINGIZE(NAME,::, BOOST_PP_CAT(last_enum_,NAME));  \
        }                                                                                                                                       \
        else                                                                                                                            \
        {                                                                                                                                       \
                return "Invalid enum value specified for " # NAME;                              \
        }                                                                                                                                       \
}                                                                                                                                               \
                                                                                                                                                \
inline                                                                                                                                  \
std::ostream& operator<<( std::ostream& os, const NAME& en )                    \
{                                                                                                                                               \
        os << to_string(en);                                                                                            \
        return os;                                                                                                                      \
}                                                                                                                                               \
                                                                                                                                                \
                                                                                                                                                \
inline                                                                                                                                  \
NAME do_enum_cast( const std::string& s, const ::xxx::enum_cast_adl_helper<NAME>& )     \
{                                                                                                                                               \
        static const std::unordered_map<std::string,NAME> map =                         \
                {                                                                                                                               \
                        XXX_TUPLE_FOR_EACH(XXX_ENUM_CASTLIST,NAME,TUPLE)                        \
                        XXX_TUPLE_FOR_EACH(XXX_ENUM_QUALIFIED_CASTLIST,NAME,TUPLE)      \
                };                                                                                                                              \
                                                                                                                                                \
        auto cit = map.find(s);                                                                                         \
        if( cit == map.end() )                                                                                          \
        {                                                                                                                                       \
                /*XXX_THROW(xxx::exception,"Invalid value '%1%' to cast to enum " #NAME ,s);*/  \
                throw std::runtime_error("Invalid value to cast to enum");              \
        }                                                                                                                                       \
        return cit->second;                                                                                                     \
}

#define XXX_ENUM(NAME,TUPLE) XXX_ENUM_INTERNAL(NAME,NAME,TUPLE)
#define XXX_ENUM_CLASS(NAME,TUPLE) XXX_ENUM_INTERNAL(class NAME,NAME,TUPLE)
#define XXX_ENUM_CLASS_TYPE(NAME,TYPE,TUPLE) XXX_ENUM_INTERNAL(class NAME : TYPE,NAME,TUPLE)
#define XXX_ENUM_TYPE(NAME,TYPE,TUPLE) XXX_ENUM_INTERNAL(NAME : TYPE,NAME,TUPLE)





#include <iostream>
#include <string>
#include <unordered_map>

namespace xxx
{

template<class T>
struct enum_cast_adl_helper { };

template<class E>
E enum_cast( const std::string& s )
{
        return do_enum_cast(s,enum_cast_adl_helper<E>());
}

template<class E>
E enum_cast( const char* cs )
{
        std::string s(cs);
        return enum_cast<E>(s);
}

} // namespace xxx


XXX_ENUM(foo,(a,b,(c,42)));

int main(int argc, const char *argv[])
{
        std::cout << "foo::a = " << foo::a << "\n";
        std::cout << "(int)foo::c = " << (int)foo::c << "\n";
        std::cout << "to_string(foo::b) = " << to_string(foo::b) << "\n";


        std::cout << "xxx::enum_cast<foo>(\"b\") = " << xxx::enum_cast<foo>("b") << "\n";
}