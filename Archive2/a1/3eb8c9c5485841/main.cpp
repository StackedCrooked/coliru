#include <iostream>
#include <type_traits>
 
enum e1 {};
enum class e2: int {};
 
int main() {
    bool e1_type = std::is_same<
        unsigned
       ,typename std::underlying_type<e1>::type
    >::value; 
 
    bool e2_type = std::is_same<
        int
       ,typename std::underlying_type<e2>::type
    >::value;
 
    e1 h;
    auto g = static_cast<typename std::underlying_type<e1>::type>(h);
    
    std::cout
    << g << " "
    << "underlying type for 'e1' is " << (e1_type?"unsigned":"non-unsigned") << '\n'
    << "underlying type for 'e2' is " << (e2_type?"int":"non-int") << '\n';
}