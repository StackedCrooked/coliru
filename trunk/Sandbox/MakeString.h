#ifndef MAKESTRING_H
#define MAKESTRING_H


#include <sstream>
#include <string>


namespace Futile {


/**
 * MakeString
 *
 * Enables logging like this:
 *
 *   LogError(SS() << "The index " << i << " exceeds the max length of " << max << ".");
 *
 */
class MakeString
{
public:
    template <typename T>
    MakeString & operator<<(const T & datum)
    {
        mBuffer << datum;
        return *this;
    }

    operator std::string() const
    { return mBuffer.str(); }

    std::string str() const
    { return mBuffer.str(); }

private:
    std::stringstream mBuffer;
};


typedef MakeString ss;


} // namespace Futile


#endif // MAKESTRING_H
