#include <iostream>
#include <string>
#include <vector>
#include <functional>

class map {
    public:
    
    template <typename F>
    void draw_loop(int min_x, int min_y, int max_x, int max_y, F&& draw_func) {
        draw_func(min_x,min_y,1);
    }
    
    void draw_specific_tile(int n, int x, int y, int ll) {
        std::cout << n << " " << x << " " << y << " " << ll << std::endl;
    }
    
    void draw()
    {
        using namespace std::placeholders;
        //auto map_draw_function = std::bind(&map::draw_specific_tile, std::ref(*this), 1, _1, _2, _3); //or
        auto map_draw_function = [&](int n, int x, int y) { this->draw_specific_tile(1,n,x,y); };
        draw_loop(7, 9, 5, 5, map_draw_function);
    }
};

int main() {
    map themap;
    themap.draw();
}