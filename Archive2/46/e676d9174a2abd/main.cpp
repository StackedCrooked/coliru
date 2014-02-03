#include<iostream>

#include <boost/preprocessor.hpp>

#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data, elem)    \
  case data::elem : return BOOST_PP_STRINGIZE(elem);

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators)        \
enum class name {                                                     \
      BOOST_PP_SEQ_ENUM(enumerators)                                  \
};                                                                    \
                                                                      \
inline static const char* ToString(name v)                                   \
{                                                                     \
  switch (v)                                                          \
  {                                                                   \
    BOOST_PP_SEQ_FOR_EACH(                                            \
        X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE,          \
        name,                                                         \
        enumerators                                                   \
        )                                                             \
    default: return "[Unknown " BOOST_PP_STRINGIZE(name) "]";         \
  }                                                                   \
}

class Test
{
    public:
    DEFINE_ENUM_WITH_STRING_CONVERSIONS(InputRegistered, (NO)(YES))
};

int main()
{
  std::cout << Test::ToString(Test::InputRegistered::NO);
  
  return 0;
}