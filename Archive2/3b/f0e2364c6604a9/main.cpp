#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <boost/iterator/transform_iterator.hpp>
#include <array>
#include <limits>
#include <cmath>

float ConvertResultValueToFloat( double value )
{
    static const float max = std::numeric_limits< float >::max();

    if( value < -max )
        return -max;

    if( value > +max )
        return +max;

    return static_cast< float >( value );
}

double ComputeSquareOriginal( double val )
{
    return val*val;
}

template<
    typename ComponentValueIterator >
float ComputeMagnitudeOriginal(
    ComponentValueIterator firstValue,
    ComponentValueIterator lastValue )
{
    double magSquared = std::accumulate(
        boost::make_transform_iterator( firstValue, &ComputeSquareOriginal ),
        boost::make_transform_iterator( lastValue, &ComputeSquareOriginal ),
        0.0 );

    return ConvertResultValueToFloat( sqrt( magSquared ) );
}

double ComputeSquareNew( double valOut, double val )
{
    return valOut = val*val;
}

template<
    typename ComponentValueIterator >
float ComputeMagnitudeNew(
    ComponentValueIterator firstValue,
    ComponentValueIterator lastValue )
{
    double magSquared = std::accumulate( firstValue, lastValue, 0.0, ComputeSquareNew );

    return ConvertResultValueToFloat( sqrt( magSquared ) );
}

int main()
{
    std::array< double, 3 > componentData = { 3.0, 4.0 };

    float magOriginal = ComputeMagnitudeOriginal(
        componentData.begin(),
        componentData.end() );

    float magNew = ComputeMagnitudeNew(
        componentData.begin(),
        componentData.end() );

    std::cout << "expected: " << 5.0 << "\n";
    std::cout << "original: " << magOriginal << "\n";
    std::cout << "new: " << magNew << "\n";
}
