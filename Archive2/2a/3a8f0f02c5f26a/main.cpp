#include <cassert>
#include <array>

struct make_it {
    int should_be_garbage;
    
    make_it () : should_be_garbage(0) {
        // This should never be called for std::array if it performs no initalisation -- i.e., produces indeterminate values uninitialized like int and member function points
        assert( false );
    }
};

int main () {
    
    std::array<make_it, 200> wee;
    
}