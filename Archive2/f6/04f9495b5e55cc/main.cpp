namespace sf
{
struct Color
{
    Color(int r, int g, int b, int a) { }
};

void paint(Color) { }
}

struct Color
{
    int r, g, b, a;
    constexpr Color(int r, int g, int b, int a = 255) : r(r), g(g), b(b), a(a) { }
    operator sf::Color () const { return sf::Color(r, g, b, a); }
};

int main()
{
    constexpr Color k(255, 128, 64); //twoja stała
    sf::paint(k); //z jego funkcją
}
