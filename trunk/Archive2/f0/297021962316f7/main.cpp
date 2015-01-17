template<typename F>
    perf_data performance(F const & f, int calls){
        std::vector<int> times(calls);
        std::generate(times.begin(),times.end(),[&](){return timer(f).count();});
        auto a = avg(times);
        auto sd = std_dev(times,a);
        perf_data result(std::chrono::high_resolution_clock::duration(a),std::chrono::high_resolution_clock::duration(sd));
        return result;
    }