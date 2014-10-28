#include <iostream>
#include <type_traits>

enum class Category
{
  One = 1,
  Two = 2,
  Three = 3
};

template <Category> struct CategoryDescriptor;

#define DECLARE(name,...) \
template <> \
struct CategoryDescriptor<Category::name> { \
  enum sub_type { __VA_ARGS__ }; \
  constexpr operator Category() const { return Category::name; } \
}; \
constexpr CategoryDescriptor<Category::name> name{}

DECLARE(One, A, B);
DECLARE(Two, C, D);
DECLARE(Three, A, C, E);

#undef DECLARE

std::ostream& operator << (std::ostream& os, Category c) {
    return os << static_cast<std::underlying_type<Category>::type>(c);
}

template <Category C>
using SubCategoryOf = typename CategoryDescriptor<C>::sub_type;

int main() {
    std::cout << "One = " << One << "\n"
                 "One.A = " << One.A << "\n"
                 "Two = " << Two << "\n"
                 "Two.D = " << Two.D << "\n"
                 "Three = " << Three << "\n"
                 "Three.A = " << Three.A << '\n';
    
    // Category names convert to Category
    auto foo = [](Category){};
    foo(Three);
    
    // Subcategory names convert to SubCategoryOf<Category>
    auto bar = [](SubCategoryOf<Two>){};
    bar(Two.C);
}
