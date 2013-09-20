#include <boost/variant.hpp>
#include <iostream>

class Image { };
class Sprite { };
class Model3D { };

using SceneObject = boost::variant<Image, Sprite, Model3D>;

namespace draw_aspect
{
    void draw(Image const& image)     { std::cout << "drawing image\n";   } 
    void draw(Sprite const& sprite)   { std::cout << "drawing sprite\n";  } 
    void draw(Model3D const& model3D) { std::cout << "drawing model3D\n"; } 

    struct draw_visitor : boost::static_visitor<> {
        template <typename T> void operator()(T const& t) const { draw(t); }
    };

    void draw(SceneObject const& sobj) { 
        static const draw_visitor _vis;
        boost::apply_visitor(_vis, sobj);
    }
}

#include <vector>

class SceneManager //controls everything in the "world" game
{
    public:
        void Add(SceneObject v) { _worldObjects.emplace_back(std::move(v)); }
        friend void draw(SceneManager const& sm) { return sm.draw(); }
    private:
        void draw() const {
            for(auto& sobj : _worldObjects)
                draw_aspect::draw(sobj);
        } 
        std::vector<SceneObject> _worldObjects; //the vector that contains all of them
};

int main()
{
    SceneManager sman;

    sman.Add(Image());
    sman.Add(Sprite());
    sman.Add(Model3D());
    sman.Add(Image());

    draw(sman);
}
