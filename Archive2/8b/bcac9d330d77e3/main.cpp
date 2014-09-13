#ifndef ENUM_H
#define ENUM_H
#include <map>
#include <vector>
#include <string>

#include <boost/preprocessor/variadic.hpp>
#include <boost/preprocessor/list.hpp>

class EnumUtil {
public:
    template<class EnumT>
    static const std::vector<EnumT> getValues();
    template<class EnumT>
    static const char* getName(EnumT) ;
};

#define CREATE_ENUM_CLASS(EnumT, list) \
    enum class EnumT {BOOST_PP_LIST_ENUM(list)};

#define CONCAT_ENUMT(r, EnumT, elem) EnumT::elem,

#define CREATE_GET_VALUES(EnumT, list) \
    template<> \
    const std::vector<EnumT> \
    EnumUtil::getValues<EnumT>() { \
        static const std::vector<EnumT> values { \
            BOOST_PP_LIST_FOR_EACH(CONCAT_ENUMT, EnumT, list) \
        }; \
        return values; \
    }

#define REGISTER_NAME(r, EnumT, elem) \
    {EnumT::elem, #elem},

#define CREATE_GET_NAME(EnumT, list) \
    template<> \
    const char* \
    EnumUtil::getName(EnumT value) { \
        static std::map<EnumT, const char *> names { \
            BOOST_PP_LIST_FOR_EACH(REGISTER_NAME, EnumT, list) \
        }; \
        return names[value]; \
    }
    

#define CREATE_UTILITES(EnumT, list) \
    CREATE_GET_VALUES(EnumT, list) \
    CREATE_GET_NAME(EnumT, list)

#define CREATE_ENUM(EnumT, ...) \
    CREATE_ENUM_CLASS(EnumT, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__)) \
    CREATE_UTILITES(EnumT, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))
#endif

//-----------------main.cpp
#include <iostream>
using namespace std;

//#include "enum.h"


CREATE_ENUM(Animal, CAT, DOG, HORSE)
CREATE_ENUM(OS, WIN, LINUX, MAC)

int main() {
    auto animal_values = EnumUtil::getValues<Animal>();
    auto os_values = EnumUtil::getValues<OS>();
    for (auto item : animal_values) {
        cout << EnumUtil::getName(item) << endl;
    }
    for (auto item : os_values) {
        cout << EnumUtil::getName(item) << endl;
    }
        
}
