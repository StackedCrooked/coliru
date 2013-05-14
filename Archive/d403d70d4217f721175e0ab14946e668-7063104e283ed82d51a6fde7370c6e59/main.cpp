#include <vector>
#include <iostream>

struct Tit {
public:
    template <typename TMilkContainer, typename TMilk = typename TMilkContainer::value_type>
    Tit ( TMilkContainer&& milkcontainer ) {
        std::cout << "Milky" << std::endl;
    }
    
    Tit () {
        
    }
    
    Tit ( Tit&& mov ) {
        std::cout << "Moving" << std::endl;    
    }
 
};

struct ManBreast : public Tit {
public:
    struct DryAsADesert {
        
    };
    
    using value_type = int;
    
    DryAsADesert d;
    
    ManBreast () {
        
    }
    
    // Invokes templated `Tit` constructor rather than mov constructor
    // on MSVC
    ManBreast ( ManBreast&& mov ) : Tit( std::move( mov ) ), d( mov.d ) {
        
    }
    
};

int main ( int argc, char** argv ) {
	
    ManBreast mb = std::move ( ManBreast() );
    
}