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

#define SAMPLES 10
#define TEST_SIZE 10000000

int main() {
    vector<float> fv(TEST_SIZE);
    vector<double> dv(TEST_SIZE);
    for (size_t i = 0; i < TEST_SIZE; ++i){
        fv.push_back(rand() * 0.1f);
        dv.push_back(rand() * 0.1);
    }

    vector<std::chrono::microseconds::rep> fv_samples(SAMPLES);
    vector<std::chrono::microseconds::rep> dv_samples(SAMPLES);

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
    }
    
    auto fv_time = accumulate(begin(fv_samples), end(fv_samples), 0) / fv_samples.size();
    auto dv_time = accumulate(begin(dv_samples), end(dv_samples), 0) / dv_samples.size();
    
    cout << "Float average time: " << fv_time << " microseconds" <<  endl;
    cout << "Double average time: " << dv_time << " microseconds" << endl;

    return 0;
}