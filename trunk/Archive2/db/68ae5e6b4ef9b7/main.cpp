#include <iostream>

template <class Range>
Range
FindFirstIf(Range rng, bool (*Function)(typename Range::ConstReference value))
{
    return rng;
}

struct range
{
    using ConstReference = const float&;
};

int
main()
{
    range rng;
    rng = FindFirstIf(rng, [](const float& val) { return (val < 0.0f); });
    std::cout << __GNUC__ << '.' << __GNUC_MINOR__ << '\n';
}

