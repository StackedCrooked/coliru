#include <iostream>
#include <type_traits>

template<typename T> struct Bagel { };

template<typename T> 
struct IsBestBagel : std::false_type { };

struct Blueberry { };

template<> 
struct IsBestBagel<Bagel<Blueberry>> : std::true_type { };

int main()
{
    struct NotBlueberry {};
    std::cout << IsBestBagel<Bagel<NotBlueberry>>{} << std::endl;
    std::cout << IsBestBagel<Bagel<Blueberry>>{} << std::endl;

    return 0;
}