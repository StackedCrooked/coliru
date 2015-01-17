#include <fstream>
#include <complex>
#include <sstream>
#include <cassert>

const int MAX_ITER = 1000;
const float minX = -1;
const float maxX = 1;
const float minY = -1;
const float maxY = 1;
const int resX = 1080;
const int resY = 768;
const int maxColor = 1000;

struct Color{
    int red;
    int green;
    int blue;
    Color(int r, int g, int b):red(r),green(g),blue(b){}
};

Color calc_iter(std::complex<float> c){
    std::complex<float> z(0,0);
    auto iter = 0;
    while(std::abs(z) < 2 && iter < MAX_ITER){
        z = z*z + c;
        iter++;
    }
    if(std::abs(z) >= 2){ //Escaped - part of the mandelbrot set, color it black
        return Color(0,0,0);
    }
    return Color(iter,0,0);
}

int main()
{
    const auto xScale = (maxX - minX) / resX;
    const auto yScale = (maxY - minY) / resY;

    std::ofstream out("Mandelbrot.ppm");
    assert(out);

    out << "P3\n";
    out << resX << " " << resY << "\n";
    out << maxColor << "\n";

    for(auto i = 0; i < resX; i++){
        for(auto j = 0; j < resY; j++){
            auto real = minX + xScale * i;
            auto imag = maxY - yScale * j;
            std::complex<float> c(real,imag);
            Color color = calc_iter(c);
            out << color.red << " " << color.green << " " << color.blue << " ";
        }
        out << "\n";
    }
    out.close();
    return 0;
}
