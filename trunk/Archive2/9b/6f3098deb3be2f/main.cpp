#include <iostream>

class Vec2D {
    public:
        Vec2D(float x, float y) : X(x), Y(y) {}
        Vec2D operator*(Vec2D& vector) {
            return Vec2D((vector.X * X), (vector.Y * Y));
        }
        float GetX() {
            return X;
        }
        float GetY() {
            return Y;
        }
    private:
        float X;
        float Y;
};

int main() {
    Vec2D Foo{1.3, 2.4};
    Vec2D Bar{5.6, 7.8};
    Vec2D Baz = Foo * Bar;
    std::cout
        << Baz.GetX()
        << ", "
        << Baz.GetY()
    << std::endl;
	return 0;
}