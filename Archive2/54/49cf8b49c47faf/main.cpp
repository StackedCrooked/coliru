#include <ratio>
#include <chrono>
using namespace std::chrono;

template <typename Rep, typename Period = std::ratio<1>>
class Frequency
{
public:
    explicit Frequency(Rep cycles) : _cycles{cycles} { }

    friend Rep operator *(const Frequency<Rep, Period>& f, const duration<Rep, Period> d)
    {
        return f._cycles * d.count();
    }
    friend Rep operator *(const duration<Rep, Period> d, const Frequency<Rep, Period>& f)
    {
        return f._cycles * d.count();
    }
private:
    Rep _cycles; ///> The number of cycles per period.
};

int main()
{
    Frequency<double> f{60.0};
    duration<double> d{1.0};
    double foo = f * d;
}