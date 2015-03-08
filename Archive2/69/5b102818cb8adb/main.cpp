# include <chrono>
# include <iostream>
# include <thread>
# include <mutex>
# include <future>

long double compute(int precision)
{
    std::cout << "Computing with precision " << precision << std::endl;
    std::this_thread::sleep_for(
        std::chrono::duration<double>(precision / 40.0));
    std::cout << "Computed!" << std::endl;
    return 1.0L / precision;
}

struct ResultGetter {
    std::future<long double> future;
    std::pair<long double, int> getResult(
        std::chrono::system_clock::time_point deadline, int maxPrecision)
    {
        long double result = 1;
        int precision = 1;
        if (std::chrono::system_clock::now() < deadline) {        
            while (precision < maxPrecision) {
                const int nextPrecision = std::min(maxPrecision, precision * 2);
                future = std::async(std::launch::async, compute, nextPrecision);
                if (future.wait_until(deadline) == std::future_status::timeout)
                    break;
                result = future.get();
                precision = nextPrecision;
            }
        }
        return { result, precision };
    }
};

int main()
{
    using namespace std::literals::chrono_literals;
    ResultGetter getter;
    const auto result = getter.getResult(
        std::chrono::system_clock::now() + 500ms, 64);
    std::cout << "Computed result " << result.first
              << " with precision " << result.second << std::endl;
}
