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
        
        auto section_size = RES_Y / thread_num;
        
        for(auto i = 0; i < thread_num; i++)
        {
            threads.push_back([&](){mandelbrot_portion(image,MIN_X,MIN_Y,i*section_size,(i+1)*section_size,xScale,yScale,color)});
        }
        for(auto&& thread : threads)
        {
            thread.join();
        }
        
        return image;
    }
    
    template<typename F>
    void mandelbrot_portion(std::vector<std::vector<Color> > const & image,
                            const int MIN_X, const int MIN_Y,
                            const int y_start, const int y_end,
                            const int xScale, const int yScale,
                            F const & color)
    {
        for(auto i = y_start; i < y_end; i++){
            for(auto j = 0; j < image[i].size(); j++){
                auto real = MIN_X + xScale * j;
                auto imag = MAX_Y - yScale * i;
                std::complex<long double> c(real,imag);
                auto iter = iterate(c);
                image[i][j] = color(iter,c);
            }
        }
    }