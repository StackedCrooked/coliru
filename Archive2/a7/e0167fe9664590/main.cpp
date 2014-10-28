#include <iostream>
#include <type_traits>

template<bool Pred, class T = void>
using enable_if_t = typename std::enable_if<Pred, T>::type;

// ---

template<int> struct TemplateHack {};

#define Template(...) \
    template< \
    Template_ADD_END(Template_A_1 __VA_ARGS__) \
    Template_ADD_END(Template_B_1 __VA_ARGS__) \
    TemplateHack<__LINE__>* = nullptr>

#define Template_ADD_END(...) Template_ADD_END2(__VA_ARGS__)
#define Template_ADD_END2(...) __VA_ARGS__ ## _END

#define Template_A_1(x) declare##x, Template_A_2
#define Template_A_2(x) declare##x, Template_A_1
#define Template_A_1_END
#define Template_A_2_END

#define Template_B_1(x) class = enable_if_t<is##x>, Template_B_2
#define Template_B_2(x) class = enable_if_t<is##x>, Template_B_1
#define Template_B_1_END
#define Template_B_2_END

// ---

#define isIntegral(T) std::is_integral<T>::value
#define declareIntegral(T) class T

#define isFloating(T) std::is_floating_point<T>::value
#define declareFloating(T) class T

#define isLessThanThree(T) (T < 3)
#define declareLessThanThree(T) int T

// ---

Template((Integral(T))(Floating(T2)))
void f(T, T2) { std::cerr << "I, F" << std::endl; }

Template((Floating(T))(Floating(T2)))
void f(T, T2) { std::cerr << "F, F" << std::endl; }

Template((Integral(T))(Integral(T2)))
void f(T, T2) { std::cerr << "I, I" << std::endl; }

Template((LessThanThree(N)))
void x() {
    std::cerr << "N < 3" << std::endl;
}

// ---

int main () {
    f(1, 'a');
    f(1, 1.0);
    f(1.0, 1.0);
    x<2>();
    // x<4>(); // Error
}