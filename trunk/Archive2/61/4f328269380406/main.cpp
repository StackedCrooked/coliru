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

struct X
{
    static constexpr Color k{255, 128, 64}; //twoja stała
};

constexpr Color X::k; //definicja potrzebna niestety

int main()
{
    sf::paint(X::k); //funkcja SFML
}
