#include <cmath>
#include <iostream>
#include <functional>

struct MemberFunctionMe {
    
    float Normalize( int raw ) {
        return raw * 2.0f;
    }
    
};

struct RememberFunctionMeToo {
    
    float Normalize( int raw ) {
        return raw * 0.5f;
    }
    
};


int main () {
    using namespace std::placeholders;
    
    MemberFunctionMe mfm;
    RememberFunctionMeToo rfmt;
    
    std::function<float( int )> f = std::bind( &MemberFunctionMe::Normalize, _1, _2 );
    std::cout << f( mfm, 1.0f ) << std::endl;
    //std::cout << f( rfmt, 1.0f ) << std::endl;
    
}
