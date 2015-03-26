#include <iostream>
#include <complex>
#include <cmath>
#include <map>
#include <vector>
#include <array>

namespace fourier
{
    using complex_t = std::complex<double>;
    const complex_t plusI = complex_t(0, 1);
    const complex_t minusI = -complex_t(0, -1);

    const std::array<int, 16> baseWaves =
    {
        0, 1, 2, 3, 4, 5, 6, 7
    };

    template<typename signal_t>
    std::map<int, complex_t> transform(const signal_t& signal)
    {
        std::map<int, complex_t> results;
        const int signalLength = signal.size();

        for(size_t linearFrequencyIndex = 0; linearFrequencyIndex < baseWaves.size(); ++linearFrequencyIndex)
        {
            complex_t sum = 0;
            const complex_t minusIByFrequency = minusI * static_cast<complex_t::value_type>(baseWaves[linearFrequencyIndex]);
            for(int signalIndex = 0; signalIndex < signalLength; ++signalIndex)
            {
                const complex_t euler = exp(minusIByFrequency * static_cast<complex_t::value_type>(signalIndex));
                sum += static_cast<complex_t::value_type>(signal[signalIndex]) * euler;
            }
            std::cout << "frequency " << baseWaves[linearFrequencyIndex] << " done" << std::endl;
            results[baseWaves[linearFrequencyIndex]] = sum / static_cast<complex_t::value_type>(signalLength);
        }

        return results;
    }
}

int main (int argc, char* argv[])
{
    std::cout << "generating test data" << std::endl;
    std::vector<int> inputA;
    for(int x = 0; x < 4096*4096; ++x)
    {
        inputA.push_back(x);
    }

    std::cout << "here goes..." << std::endl;
    auto inputATransformed = fourier::transform(inputA);
    std::cout << "done!" << std::endl;

    for(auto element : inputATransformed)
    {
        std::cout << element.first << " -> " << element.second << std::endl;
    }

    std::cin.get();
}