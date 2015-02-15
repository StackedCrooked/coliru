#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <limits>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define X_RES 800
#define Y_RES 600
#define SAMPLES 8
#define DEPTH   8

using namespace std;


// structs
typedef array<float,3> pixel;

struct object {
    array<float,3> pos;
    float scale;
};

// globals
vector<object> objects;

// functions
template <class T, size_t N>
T vec_magnitude( array<T,N> x ) {
    float value = 0;

    for( unsigned int i = 0; i < N; i++ ) {
        value += pow( x[i], 2.f );
    }

    return sqrt( value );
}

template <class T, size_t N>
array<T, N> normalize( array<T, N> vec ) {
    T mag = vec_magnitude( vec );
    for( int i = 0; i < N; i++ ) {
        vec[i] /= mag;
    }

    return vec;
}

template <class T, size_t N>
array<T, N> vec_mult( array<T, N> x, array<T, N> y ) {
    for( unsigned int i = 0; i < N; i++ )
        x[i] *= y[i];

    return x;
}

template <class T, size_t N>
T vec_dot( array<T, N> x, array<T, N> y ) {
    T dot = 0;

    for( unsigned int i = 0; i < N; i++ )
        dot += x[i] * y[i];

    return dot;
}

template <class T, size_t N>
T vec_angle( array<T,N> x, array<T,N> y ) {
    return acos( vec_dot(x,y) / (vec_magnitude(x)*vec_magnitude(y)) );
}

//------------------------------------------------------------------------------

float test( array<float,3> pos, array<float,3> ray_vec, object o ) {
    for( unsigned int i = 0; i < 3; i++ )
        pos[i] = o.pos[i] - pos[i];

    array<float,3> pos_vec = normalize( pos );

    float angle = vec_angle( pos_vec, ray_vec );

    if( sin(angle)*vec_magnitude(pos) < o.scale/2 )
        return sqrt(pow(vec_magnitude(pos),2) + pow(o.scale/2,2));

    return numeric_limits<float>::infinity();
}

pixel trace( array<float,3> pos, array<float,3> ray_vec, unsigned int d = DEPTH ) {
    float closest_hit = numeric_limits<float>::infinity();
    object *hit_object = NULL;

    for( auto &o : objects ) {
        float distance = test(pos,ray_vec, o);
        if( distance < closest_hit ) {
            hit_object = &o;
            closest_hit = distance;
        }
    }

    return {closest_hit, closest_hit, closest_hit};
}

//------------------------------------------------------------------------------

array<
    array<pixel, Y_RES>,
    X_RES
> *buffer;

int main() {
    buffer = new array<array<pixel,Y_RES>,X_RES>;
    array<array<pixel,Y_RES>,X_RES> &image = *buffer;

    sf::Image img;
    img.create( X_RES, Y_RES, sf::Color::Black );
    sf::Texture tex;
    tex.loadFromImage(img);
    sf::Sprite s( tex );

    sf::RenderWindow app;
    app.create( sf::VideoMode(X_RES, Y_RES),
                "xray",
                sf::Style::Default ^ sf::Style::Resize );


    objects.resize(1);
    objects[0].pos = {0, 0,  -5};
    objects[0].scale = 2;
    objects[1].pos = {10, 0, -25};
    objects[1].scale = 1;

    while( app.isOpen() ) {
        float length = numeric_limits<float>::infinity();
        for( unsigned int x = 0; x < X_RES; x++ ) {
            for( unsigned int y = 0; y < Y_RES; y++ ) {
                array<float,3> direction;

                direction[0] = sin( ((float)x/X_RES*2-1)*(M_PI/8) );
                direction[1] = sin( ((float)y/Y_RES*2-1)*(M_PI/8) );
                direction[2] = cos( ((float)x/X_RES*2-1)*(M_PI/8) );

                direction = normalize( direction );

                image[x][y] = trace( {0, 0, 0},
                                     direction );

                if( length > image[x][y][0] )
                    length = image[x][y][0];
           }
        }

        // lol hax
        unsigned long long hits = 0, misses = 0;

        for( unsigned int y = 0; y < Y_RES; y++ ) {
            for( unsigned int x = 0; x < X_RES; x++ ) {
                if( image[x][y][0] < numeric_limits<float>::infinity() ) {
                    float intensity = image[x][y][0]/length*255;

                    img.setPixel( x, y, sf::Color( intensity,
                                                     intensity,
                                                     intensity ));
                    hits++;
                } else {
                    misses++;
                }
            }
        }

        cout << "hits:   " << hits << endl;
        cout << "misses: " << misses << endl;

        tex.loadFromImage( img );
        app.draw(s);
        app.display();

        sf::Event e;
        while( app.pollEvent(e) ) {
            switch( e.type ) {
            case sf::Event::Closed:
                app.close();
                break;
            default:
                cout << "e: " << e.type << endl;
                break;
            }
        }
    }

    delete buffer;
}