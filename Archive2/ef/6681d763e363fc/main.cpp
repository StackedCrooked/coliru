#include <iostream>

struct Pixel {
    Pixel(unsigned x = 1920, unsigned y = 1080) : X(x), Y(y) {}
    unsigned X;
    unsigned Y;

    friend std::ostream& operator<<(std::ostream& os, Pixel const& p) {
        return os << "Pixel(" << p.X << ", " << p.Y << ")";
    }
};

struct TransformMatrix {
    constexpr TransformMatrix(float aWidth = 640/1920.f, float aHeigth = 480/1080.f) : W(aWidth), H(aHeigth) {}

    Pixel operator()(const Pixel &aPixel) const {
        return { static_cast<unsigned>(aPixel.X * W), static_cast<unsigned>(aPixel.Y * H) };
    }
    float W;
    float H;
};

int main() {
    Pixel aPixel;
    TransformMatrix xfrm;

    std::cout << aPixel << " -> " << xfrm(aPixel) << "\n";
}
