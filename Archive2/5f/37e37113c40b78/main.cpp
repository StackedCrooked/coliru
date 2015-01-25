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

        for(auto i = 0; i < RES_Y; i++){
            for(auto j = 0; j < RES_X; j++){
                auto real = MIN_X + xScale * j;
                auto imag = MAX_Y - yScale * i;
                std::complex<long double> c(real,imag);
                auto iter = iterate(c);
                image[i][j] = color(iter,c);
            }
        }
        return image;
    }