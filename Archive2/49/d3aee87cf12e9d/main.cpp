#include <fstream>
#include <complex>
#include <sstream>
#include <cassert>
#include <vector>
#include <array>
#include <algorithm>

const int MAX_ITER = 1000;
const long double MIN_X = -2;
const long double MAX_X = 2;
const long double MIN_Y = -2;
const long double MAX_Y = 2;
const long double ESCAPE = 2;
const int RES_X = 1080;
const int RES_Y = 768;
const int MAX_COLOR = 1000;

struct Color{
    int red;
    int green;
    int blue;
    Color(int r, int g, int b):red(r),green(g),blue(b){}
};

int calc_iter(std::complex<long double> c){
    std::complex<long double> z(0,0);
    auto iter = 0;
    while(std::abs(z) < ESCAPE && iter < MAX_ITER){
        z = z*z + c;
        iter++;
    }
    return iter;
}

Color get_color(long double val){
    //TODO - map val -> RGB
    return Color{1000,1000,1000};
}

int main()
{
    const auto xScale = (MAX_X - MIN_X) / RES_X;
    const auto yScale = (MAX_Y - MIN_Y) / RES_Y;

    //Calculate iteration numbers for each pixel and distribute them to a histogram
    //Keeping track of the total number of iterations of mandelbrot equation made
    std::array<std::array<int,RES_X>, RES_Y> iterations;
    std::array<int,MAX_ITER> histogram;
    std::generate(histogram.begin(),histogram.end(),[](){ return 0; });
    long double total_iter = 0;

    for(auto i = 0; i < RES_Y; i++){
        for(auto j = 0; j < RES_X; j++){
            auto real = MIN_X + xScale * j;
            auto imag = MAX_Y - yScale * i;
            std::complex<long double> c(real,imag);
            auto iter = calc_iter(c);
            iterations[i][j] = iter;
            /*
            Color color(1000,1000,1000);
            if(iter >= MAX_ITER){ //Didn't escape - part of mandelbrot set - color it black
                color = Color{0,0,0};
            }
            out << color.red << " " << color.green << " " << color.blue << "    ";
            */
            histogram[iter]++;
            total_iter++;
        }
    }    


    //Normalize the color of each pixel and output it to the file
    std::ofstream out("Mandelbrot.ppm");
    assert(out);

    out << "P3\n";
    out << RES_X << " " << RES_Y << "\n";
    out << MAX_COLOR << "\n";

    std::array<std::array<float,RES_X>,RES_Y> color_val;

    for(auto i = 0; i < RES_Y; i++){
        for(auto j = 0; j < RES_X; j++){
            long double color = 0;
            auto iter = iterations[i][j];
            if(iter >= MAX_ITER){ //Part of mandelbrot set - color Black
                out << "0 0 0   ";
            }else{ //Not part of mandelbrot set - color based on iter number
                color_val[i][j] = histogram[iter] / total_iter;
                auto color = get_color(color_val[i][j]);
                out << color.red << " " << color.green << " " << color.blue << "    ";
            }
        }
        out << "\n";
    }

    out.close();
    return 0;
}
