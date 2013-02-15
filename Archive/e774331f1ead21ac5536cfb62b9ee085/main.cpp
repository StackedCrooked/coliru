#include <initializer_list>
#include <array>
#include <iostream>
#include <utility>

struct Special {
private:
    int arf;

public:
    
    Special (int a) : arf(a) {
        
    }
    
    Special (float a) : arf(a) {
        
    }
    
    Special (double a) : arf(a) {
        
    }
    
    int Get() {
        return arf;   
    }


    template < typename ...Args >
    static Special Format ( const Special& format, const Args&... args ) {
        Special value = format;
        
    	std::array< const Special*, sizeof...(args) > argtable = {
    		&std::forward<const Special>( args )...
    	};
        
        // Do crazy shit with each of the arguments, related to the original SpecialType format...
        for ( auto s : argtable ) {
            value.arf += s->arf;
        }
        
        return value;
    }
    
};

int main ( int argc, char* argv[] ) {
	Special type = Special::Format( 5, 0, 1.96f, 2.37 );
    
    std::cout << type.Get() << std::endl;
    
    return 0;
}