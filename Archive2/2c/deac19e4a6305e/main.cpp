#ifndef MANDELBROT_H
#define MANDELBROT_H

#include<vector>
#include<complex>
#include<thread>

namespace Mandelbrot{
    const int MAX_ITER = 1000;
    const long double ESCAPE = 2;
    const int MAX_COLOR = 255;

    struct Color
    {
        int red;
        int green;
        int blue;
        Color():red(0),green(0),blue(0){}
        Color(int r, int g, int b):red(r),green(g),blue(b){}
        Color(Color const & other):red(other.red),green(other.green),blue(other.blue){}
    };

    //Helper functions
    Color hsl_to_rgb(double, double, double);
    int iterate(std::complex<long double>&);
    Color interpolate(Color first, Color second, long double p);

    //Print an image based on a 2D vector of colors
    void print_to_ppm(std::string filename, std::vector<std::vector<Color> > const& image);

    //Generates a 2D vector with the mandelbrot image
    template<typename F>
    std::vector<std::vector<Color> >
    mandelbrot(const int thread_num, const int RES_X, const int RES_Y,
                    const long double MIN_X, const long double MAX_X,
                    const long double MIN_Y, const F & color)
    {
        long double MAX_Y = MIN_Y + (MAX_X - MIN_X)*(static_cast<float>(RES_Y)/RES_X);
        const auto xScale = (MAX_X - MIN_X) / RES_X;
        const auto yScale = (MAX_Y - MIN_Y) / RES_Y;

        std::vector<std::vector<Color> > image(RES_Y,std::vector<Color>(RES_X));
        std::vector<std::thread> threads;

        for(auto i = 0; i < thread_num; i++)
        {
            threads.push_back(std::thread{[&image,MIN_X,MAX_Y,i,thread_num,xScale,yScale,color](){
                mandelbrot_portion(image,MIN_X,MAX_Y,
                                   i,thread_num,
                                   xScale,yScale,color);}});
        }
        for(auto&& thread : threads)
        {
            thread.join();
        }

        return image;
    }

    template<typename F>
    void mandelbrot_portion(std::vector<std::vector<Color> >& image,
                            const long double MIN_X, const long double MAX_Y,
                            const int offset, const int step,
                            const long double xScale, const long double yScale,
                            F const & color)
    {
        for(auto i = offset; i < image.size(); i+=step){
            for(auto j = 0; j < image[i].size(); j++){
                auto real = MIN_X + xScale * j;
                auto imag = MAX_Y - yScale * i;
                std::complex<long double> c(real,imag);
                auto iter = iterate(c);
                image[i][j] = color(iter,c);
            }
        }
    }

    //Available coloring functions
    Color smooth_grad  (int iter, std::complex<long double> const & final, Color const & color1, Color const & color2);
    Color smooth_hue   (int iter, std::complex<long double> const & final, int sat, int light);
    Color discrete_grad(int iter, std::complex<long double> const & final, Color const & color1, Color const & color2);
    Color discrete_hue (int iter, std::complex<long double> const & final, int sat, int light);
    Color dwell_bands  (int iter, std::complex<long double> const & final, std::vector<Color> const & palette);
    Color boolean      (int iter, std::complex<long double> const & final, Color const & color1, Color const & color2);

    //Coloring function facilitator objects
    struct smooth_grad_colorer
    {
        Color color1, color2;
        smooth_grad_colorer(Color c1, Color c2):color1(c1),color2(c2){}
        Color operator()(int iter, std::complex<long double> const& final) const
        {
            return smooth_grad(iter,final,color1,color2);
        }
    };

    struct smooth_hue_colorer
    {
        int sat, light;
        smooth_hue_colorer(int s, int l):sat(s),light(l){}
        Color operator()(int iter, std::complex<long double> const& final) const
        {
            return smooth_hue(iter,final,sat,light);
        }
    };

    struct discrete_grad_colorer
    {
        Color color1, color2;
        discrete_grad_colorer(Color c1, Color c2):color1(c1),color2(c2){}
        Color operator()(int iter, std::complex<long double> const& final) const
        {
            return discrete_grad(iter,final,color1,color2);
        }
    };

    struct discrete_hue_colorer
    {
        int sat, light;
        discrete_hue_colorer(int s, int l):sat(s),light(l){}
        Color operator()(int iter, std::complex<long double> const& final) const
        {
            return discrete_hue(iter,final,sat,light);
        }
    };

    struct boolean_colorer
    {
        Color color1, color2;
        boolean_colorer(Color c1, Color c2):color1(c1),color2(c2){}
        Color operator()(int iter, std::complex<long double> const& final) const
        {
            return boolean(iter,final,color1,color2);
        }
    };

    struct dwell_bands_colorer
    {
        std::vector<Color> palette;
        dwell_bands_colorer(std::vector<Color> p):palette(p){}
        Color operator()(int iter, std::complex<long double> const& final) const
        {
            return dwell_bands(iter,final,palette);
        }
    };
}

#endif // MANDELBROT_H
