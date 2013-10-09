
    #include <iostream>
    #define BOOST_PP_VARIADICS //  de van.
    #include <boost/preprocessor/list/for_each.hpp>
    #include <boost/preprocessor/variadic/to_list.hpp>
    #include <boost/preprocessor/variadic/size.hpp>
    #include <boost/preprocessor/facilities/expand.hpp>
    #include <boost/preprocessor/control/if.hpp>
    #include <set>
     
     
    #define COMPARE_IMPL2(r, _, attribute) \
            if(lhs.attribute != rhs.attribute) return lhs.attribute < rhs.attribute; \
     
    #define COMPARE_IMPL1(attributeList) \
            BOOST_PP_LIST_FOR_EACH(COMPARE_IMPL2, _, attributeList) \
     
    #define COMPARE(T, U, ...) \
            struct {\
            bool operator()(const T& lhs, const U& rhs) { \
                    COMPARE_IMPL1(BOOST_PP_EXPAND(BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))) \
                    return false; \
            }} \
     
    struct A {
            int a1, a2, a3;
    };
     
    int main() {
        using C = COMPARE(A, A, a1, a2, a3);
        std::set<A, C> s;
        s.insert({1,2,3});
        s.insert({1,2,5});
        s.insert({1,1,3});
        s.insert({1,2,8});
        s.insert({0,2,3});
        s.insert({0,2,8});
        
        for (auto& a: s) {
            std::cout << a.a1 << " " << a.a2 << " " << a.a3 << std::endl;
        }
    }

