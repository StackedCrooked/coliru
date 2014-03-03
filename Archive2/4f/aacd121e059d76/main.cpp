#include <cstddef>
#include <iostream>
#include <array>

std::array<float, 2> get_coords ( int current_num, int max_num, float width, float height ) {
    std::array<float, 2> texel;
    // Use your brain and do the math here
    return texel;
}

int main () {
    
    int sprite_num = 0;
    int sprite_max = 6;
    float sprite_width = 300;
    float sprite_height = 50;
    while ( true ) {
        if ( sprite_num == sprite_max )
            break;
            
        std::array<float, 2> texcoord = get_coords( sprite_num, max_num, sprite_width, sprite_height );
        // now you have the texture coordinates you need! Use them in the glBegin/glEnd loop
        // The magic is that because it's a variable, you only need to do it ONCE
        // HOW EXICITING!!!!!!!!!!!!!!!!!!!!!!!!!
        sprite_num++;
    }
    
}

