#include <iostream>

class Image { };
class Sprite { };
class Model3D { };

namespace draw_aspect
{
    void draw(Image const& image)     { std::cout << "drawing image\n";   } 
    void draw(Sprite const& sprite)   { std::cout << "drawing sprite\n";  } 
    void draw(Model3D const& model3D) { std::cout << "drawing model3D\n"; } 
}

#include <vector>

class SceneManager //controls everything in the "world" game
{
    public:
        void Add(Image v)   { _images  .emplace_back(std::move(v)); }
        void Add(Sprite v)  { _sprites .emplace_back(std::move(v)); }
        void Add(Model3D v) { _model3Ds.emplace_back(std::move(v)); }

        friend void draw(SceneManager const& sm) { return sm.draw(); }
    private:
        void draw() const {
            for(auto& sobj : _images)   draw_aspect::draw(sobj);
            for(auto& sobj : _sprites)  draw_aspect::draw(sobj);
            for(auto& sobj : _model3Ds) draw_aspect::draw(sobj);
        } 
        std::vector<Image> _images;
        std::vector<Sprite> _sprites;
        std::vector<Model3D> _model3Ds;
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
