# include <chrono>
# include <iostream>
# include <thread>
namespace Chrono = std::chrono;
template <typename Duration, typename Computation>
Duration measureComputationTime(Computation f)
{
    using Clock = Chrono::steady_clock;
    const auto start = Clock::now();
    f();
    const auto end = Clock::now();
    return Chrono::duration_cast<Duration>(end - start);
}
using namespace std::literals::chrono_literals;
void findAnAnswerToMyQuestion() { std::this_thread::sleep_for(2ms); }
int main()
{
    std::cout << "Finding an answer took " <<
        measureComputationTime<Chrono::microseconds>(
             findAnAnswerToMyQuestion).count() << "us.\n";
}