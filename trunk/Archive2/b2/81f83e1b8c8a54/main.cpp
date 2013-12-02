#include <iostream>
#include <type_traits>
#include <tuple>
#include <utility>

void breaking( ) {
    std::cout << "Nice!~\n";
}

template <typename TFx>
void something ( TFx&& arg ) {
    typedef typename std::decay<TFx>::type clean_fx;
    const static bool isfunction = std::is_function<clean_fx>::value;
    struct { } _ = typename std::decay<TFx>::type();
    static_assert( isfunction, "FUCK!" );
	    
}

int main () {
    
    something( breaking );
    
}