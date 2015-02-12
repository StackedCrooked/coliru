    #include <algorithm>
    #include <array>
    #include <cmath>
    #include <iostream>
    #include <limits>
    
    #define X_RES 80
    #define Y_RES 24
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
    template <class T, unsigned long N>
    T vec_magnitude( array<T,N> x ) {
        float value = 0;
    
        for( unsigned int i = 0; i < N; i++ ) {
            value += pow( x[i], 2.f );
        }
    
        return sqrt( value );
    }
    
    template <class T, unsigned long N>
    array<T, N> normalize( array<T, N> vec ) {
        T mag = vec_magnitude( vec );
        for( int i = 0; i < N; i++ ) {
            vec[i] /= mag;
        }
        
        return vec;
    }
    
    template <class T, unsigned long N>
    array<T, N> vec_mult( array<T, N> x, array<T, N> y ) {
        for( unsigned int i = 0; i < N; i++ )
            x[i] *= y[i];
    
        return x;
    }
    
    template <class T, unsigned long N>
    T vec_dot( array<T, N> x, array<T, N> y ) {
        T dot = 0;
    
        for( unsigned int i = 0; i < N; i++ )
            dot += x[i] * y[i];
    
        return dot;
    }
    
    template <class T, unsigned long N>
    T vec_angle( array<T,N> x, array<T,N> y ) {
        return acos( vec_dot(x,y) / (vec_magnitude(x)*vec_magnitude(y)) );
    }
    
    //------------------------------------------------------------------------------
    
    float test( array<float,3> pos, array<float,3> ray_vec, object o ) {
        for( unsigned int i = 0; i < 3; i++ )
            pos[i] = o.pos[i] - pos[i];
    
        array<float,3> pos_vec = normalize( pos );
    
        float angle = vec_angle( pos_vec, ray_vec );
    
        if( sin(angle)*vec_magnitude(pos) < 1 )
            return vec_magnitude(pos);
    
        return numeric_limits<float>::infinity();
    }
    
    pixel trace( array<float,3> pos, array<float,3> ray_vec, unsigned int d = DEPTH ) {
        float closest_hit = numeric_limits<float>::infinity();
        object *hit_object = NULL;
    
        for( auto &o : objects ) {
            float distance = test(pos,ray_vec, o);
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
    
        objects.resize(2);
        objects[0].pos = {0, 0,  -5};
        objects[1].pos = {10, 0, -25};
        for( unsigned int x = 0; x < X_RES; x++ ) {
            for( unsigned int y = 0; y < Y_RES; y++ ) {
                array<float,3> direction;
                
                direction[0] = sin( ((float)x/X_RES*2-1)*(M_PI/8) );
                direction[1] = sin( ((float)y/Y_RES*2-1)*(M_PI/8) );
                direction[2] = cos( ((float)x/X_RES*2-1)*(M_PI/8) );
        
                direction = normalize( direction );
        
                image[x][y] = trace( {0, 0, 0},
                                     direction );
           }
        }
    
        // lol hax
        for( unsigned int y = 0; y < Y_RES; y++ ) {
        for( unsigned int x = 0; x < X_RES; x++ ) {
            if( image[x][y][0] > 0.5 ) {
                cout << "#";
                hits++;
            } else {
                cout << " ";
                misses++;
            }
        } cout << endl; }
    
        cout << "hits:   " << hits << endl;
        cout << "misses: " << misses << endl;
    }