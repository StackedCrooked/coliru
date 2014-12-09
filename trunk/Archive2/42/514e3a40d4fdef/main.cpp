#include <array>
#include <vector>

template <typename T, size_t N>
using DataPoint = std::array<T, N>;

template <typename... DataPointTypes>
using Correspondence = std::tuple<DataPointTypes...>;

//template <typename CorrespondenceTypes>
template <typename... DataPointTypes>
using CorrespondenceSet = std::vector<Correspondence<DataPointTypes...>>;

template <size_t SampleSize, typename... DataPointTypes>
using CorrespondenceSample = std::array<Correspondence<DataPointTypes...>, SampleSize>;

//template <typename Hypothesis>
template <size_t SampleSize, typename... DataPointTypes>
using HypothesisSet = std::vector<CorrespondenceSample<SampleSize, DataPointTypes...>>;
    
int main()
{
}