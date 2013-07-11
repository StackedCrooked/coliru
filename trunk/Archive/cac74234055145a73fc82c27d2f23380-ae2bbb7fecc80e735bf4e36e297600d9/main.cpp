#include <iostream>
#include <tuple>

#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/member.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/at_c.hpp>

namespace mpl = boost::mpl;
using namespace boost::type_erasure;

struct bitmap{ std::string name; };
struct coordinates{ int x, y; };

BOOST_TYPE_ERASURE_MEMBER((has_blit), blit, 2)

typedef mpl::vector<has_blit<void(bitmap, coordinates)>> is_surface;
typedef any<is_surface, _self&> surface;

BOOST_TYPE_ERASURE_MEMBER((has_paint), paint, 1)

typedef mpl::vector<has_paint<void(surface)>> is_paintable;
typedef any<is_paintable, _self&> paintable;

struct button_view {
    bitmap my_bitmap;
    
    button_view() {
        my_bitmap.name = "button.bmp";
    }
    
    void paint(surface s) {
        std::cout << "button_view::paint()" << std::endl;
        s.blit(my_bitmap, coordinates());
    }
};

struct surface_mapper {
    surface parent;
    coordinates mc;
    surface_mapper(surface p_, coordinates c_) : parent(p_) , mc(c_) {}
    
    void blit(bitmap b, coordinates c) {
        std::cout << "surface_mapper::blit()" << std::endl;
        c.x += mc.x;
        c.y += mc.y;
        parent.blit(b, c);
    }
};

struct paint {
    surface sur;
    paint(surface sur_) : sur(sur_) {}
    
    template<typename T>
    void operator()(T& t) const
    {
        surface_mapper m(sur, std::get<1>(t));
        std::get<0>(t).paint(m);
    }
};

template<typename T>
struct placed : public std::tuple<T, coordinates> {
    void move(coordinates c) {
        std::get<1>(*this) = c;
    }
};

template<typename... T>
struct composite_view {
    boost::fusion::vector<placed<T>...> views;
    
    void paint(surface s) {
        boost::fusion::for_each(views, ::paint(s));
    }
};

struct hud_view {
    bitmap my_bitmap;
    
    hud_view() {
        my_bitmap.name = "hud.bmp";
        }
    
    void paint(surface s) {
        std::cout << "hud_view::paint()" << std::endl;
        s.blit(my_bitmap, coordinates());
    }
};

struct window {
    void blit(bitmap b, coordinates c) {
        std::cout << "window::blit(" << b.name << " " << c.x << " " << c.y << ")" << std::endl;
    }
};

template<typename... T>
struct screen_base {
    boost::fusion::vector<placed<T>...> views;
    window wnd;
    
    void draw() {
        boost::fusion::for_each(views, paint(wnd));
    }
};

// user code
struct panel_view : composite_view<button_view, button_view, button_view> {
    panel_view() {
        boost::fusion::at_c<0>(views).move({1, 2});
        boost::fusion::at_c<1>(views).move({5, 2});
        boost::fusion::at_c<2>(views).move({9, 2});
    }
};

struct screen : public screen_base<button_view, panel_view, hud_view> {
    screen() {
        boost::fusion::at_c<0>(views).move({1, 2});
        boost::fusion::at_c<1>(views).move({1, 20});
        boost::fusion::at_c<2>(views).move({1, 25});
    }
};

int main()
{
    screen scr;
    scr.draw();
}
