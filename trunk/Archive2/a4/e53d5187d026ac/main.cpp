#include <cassert>

constexpr int getClamped(int mValue, int mMin, int mMax) noexcept
{
    return ( mMin <= mMax ) ? 
           ( mValue < mMin ? mMin : (mValue > mMax ? mMax : mValue) ) :
           throw "mMin must be less than or equal to mMax";
}

int main( int argc, char** argv )
{
    // These two work:
    static_assert( getClamped( 42, 0, 100 ) == 42, "CT" );
    assert( getClamped( argc, 0, 100 ) == argc );

    // Fails at compile-time:
    // static_assert( getClamped( 42, 100, 0 ) == 42, "CT" );
    
    // Fails at run-time:
    // assert( getClamped( 42, 100, 0 ) == 42 );
}
