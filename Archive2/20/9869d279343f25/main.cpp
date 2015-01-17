#include <fstream>
#include <complex>
#include <sstream>
#include <cassert>

const int MAX_ITER = 1000;
const long double minX = -2;
const long double maxX = 2;
const long double minY = -2;
const long double maxY = 2;
const long double escape = 2;
const int resX = 1080;
const int resY = 768;
const int maxColor = 1000;

struct Color{
    int red;
    int green;
    int blue;
    Color(int r, int g, int b):red(r),green(g),blue(b){}
};

Color calc_iter(std::complex<long double> c){
    std::complex<long double> z(0,0);
    auto iter = 0;
    while(std::abs(z) < escape && iter < MAX_ITER){
        z = z*z + c;
        iter++;
    }
    if(iter >= MAX_ITER){ //Didn't escape - part of mandelbrot set - color it black
        return Color(0,0,0);
    }
    return Color(iter,0,0); //Escaped - color based on iteration number
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
            std::complex<long double> c(real,imag);
            Color color = calc_iter(c);
            out << color.red << " " << color.green << " " << color.blue << " ";
        }
        out << "\n";
    }
    out.close();
    return 0;
}
