#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

struct CVector3f { float vec[3]; };

void Parse(const char* vectorString, CVector3f& outputVector)
{
    std::vector<std::string> parts;
    boost::split(parts, vectorString, boost::is_any_of(","));
    
    if (parts.size() <= 3)
    {
        std::transform(
            parts.begin(),
            parts.end(),
            outputVector.vec,
            &boost::lexical_cast<float, std::string>);
    }
}

int main()
{
    CVector3f vec;
    Parse("1.11,2.222,3.3", vec);
    
    std::cout
        << "X: " << vec.vec[0] << std::endl
        << "Y: " << vec.vec[1] << std::endl
        << "Z: " << vec.vec[2] << std::endl;
}