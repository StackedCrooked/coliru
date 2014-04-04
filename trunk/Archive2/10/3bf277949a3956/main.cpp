#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include <cmath>
using namespace std;


template<typename TimeT = std::chrono::microseconds>
struct timeit
{
    template<typename F>
    static typename TimeT::rep execution(F const &func)
    {
        auto start = std::chrono::system_clock::now();
        func();
        auto duration = std::chrono::duration_cast<TimeT>(
            std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

template <class T>
inline void Average(const vector<T>& data, double &result){
    result = 0.0;
    for (size_t i = 0; i < data.size(); ++i) {
        result += data[i];
    }

    result /= data.size();
}

template <class T>
struct alignas(16) sse_f {
    T v;
    operator T() const { return v; }
    sse_f() : v() {}
    sse_f(const T& t) : v(t) {}
    sse_f(T&& t) : v(move(t)) {}
    T& operator=(const T& t) { v = t; return *this; }
    T& operator=(T&& t) { v = move(t); return *this; }
};

#define SAMPLES 10
#define TEST_SIZE 10000000

int main() {
    vector<sse_f<float>> fv(TEST_SIZE);
    vector<sse_f<double>> dv(TEST_SIZE);
    vector<float> s_fv(TEST_SIZE);
    vector<double> s_dv(TEST_SIZE);
    for (size_t i = 0; i < TEST_SIZE; ++i){
        fv.push_back(rand() * 0.1f);
        s_fv.push_back(fv.back());
        dv.push_back(rand() * 0.1);
        s_dv.push_back(dv.back());
    }

    vector<std::chrono::microseconds::rep> fv_samples(SAMPLES);
    vector<std::chrono::microseconds::rep> dv_samples(SAMPLES);
    
    vector<std::chrono::microseconds::rep> s_fv_samples(SAMPLES);
    vector<std::chrono::microseconds::rep> s_dv_samples(SAMPLES);

    for (size_t i = 0; i < SAMPLES; ++i){
        double r1, r2;
        dv_samples[i] = timeit<>::execution([&]{
            Average(dv, r2);
        });
        fv_samples[i] = timeit<>::execution([&]{
            Average(fv, r1);
        });
        if (abs(r1 - r2) > numeric_limits<double>::epsilon()){
            cerr << "different" << endl; //эта фигня, чтобы оптимизатор не выкидывал вычисления :)
        }
        s_dv_samples[i] = timeit<>::execution([&]{
            Average(s_dv, r2);
        });
        s_fv_samples[i] = timeit<>::execution([&]{
            Average(s_fv, r1);
        });
        if (abs(r1 - r2) > numeric_limits<double>::epsilon()){
            cerr << "different" << endl; //эта фигня, чтобы оптимизатор не выкидывал вычисления :)
        }
    }
    
    auto fv_time = accumulate(begin(fv_samples), end(fv_samples), 0) / fv_samples.size();
    auto dv_time = accumulate(begin(dv_samples), end(dv_samples), 0) / dv_samples.size();
    auto s_fv_time = accumulate(begin(s_fv_samples), end(s_fv_samples), 0) / s_fv_samples.size();
    auto s_dv_time = accumulate(begin(s_dv_samples), end(s_dv_samples), 0) / s_dv_samples.size();    
    
    cout << "Aligned Float average time: " << fv_time << " microseconds" <<  endl;
    cout << "Aligned Double average time: " << dv_time << " microseconds" << endl;
    
    cout << "Float average time: " << s_fv_time << " microseconds" <<  endl;
    cout << "Double average time: " << s_dv_time << " microseconds" << endl;

    return 0;
}