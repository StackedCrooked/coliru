#include <algorithm>
#include <array>
#include <iostream>
#include <limits>

#define X_RES 1024
#define Y_RES 600
#define SAMPLES 8
#define DEPTH   8

using namespace std;


// structs
typedef array<float,3> pixel;

struct object {
    array<float,3> pos;
    array<float,4> rot;
    enum type_t {
        CUBE,
        SPHERE,
        PLANE,
    } type;
};

// globals
vector<object> objects;

// functions
template <class T, int N>
T euclidian_magnitude( array<T,N> x ) {
    float value = 0;

    for( unsigned int i = 0; i < N; i++ ) {
        value += pow( x[i], 2.f );
    }

    return sqrt( value );
}

//------------------------------------------------------------------------------

bool test( array<float,3> pos, array<float,2> vec, object o ) {
    float angle;

    for( unsigned int i = 0; i < 3; i++ )
        pos[i] = o.pos[i] - pos[i];

    return false;
}

pixel trace( array<float,3> pos, array<float,2> vec, unsigned int d = DEPTH ) {
    float closest_hit = numeric_limits<float>::infinity();
    object *hit_object = NULL;

    for( auto &o : objects ) {
        float distance = test(pos,vec, o);
        if( distance < closest_hit )
            hit_object = &o;
    }

    // XXX TODO FIXME
    if( hit_object )
        return {1, 1, 1};

    return {0, 0, 0};
}

//------------------------------------------------------------------------------

int main() {
    pixel image[X_RES][Y_RES];
    unsigned long long hits = 0, misses = 0;

    for( unsigned int x = 0; x < X_RES; x++ )
    for( unsigned int y = 0; y < Y_RES; y++ ) {
        image[x][y] = trace( {0, 0, 0},
                             {0, 0} );

        if( image[x][y][0] > 0.5 )
            hits++;
        else
            misses++;
    }
    
    cout << "hits:   " << hits << endl;
    cout << "misses: " << misses << endl;
}