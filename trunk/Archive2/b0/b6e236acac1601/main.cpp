
#define _USE_MATH_DEFINES

#include <cmath>
#include <array>

template<class PRECISION>
class Ecef: public std::array<PRECISION,3>
{
public:
    typedef std::array<PRECISION,3> Base;
    typedef PRECISION Value;

    Ecef():
        Base({0,0,0})
    {}

    Ecef(const Base &base):
        Base(base)
    {}

    Ecef(Value lat, Value lon, Value h):
        Base({lat,lon,h})
    {}

    Ecef(const Ecef &other) = default;
    Ecef &operator=(const Ecef &other) = default;

    inline Value &latitude()  { return (*this)[0]; }
    inline Value &longitude() { return (*this)[1]; }
    inline Value &height()    { return (*this)[2]; }

    inline const Value &latitude()  const { return ((const Ecef*)this)->latitude(); }
    inline const Value &longitude() const { return ((const Ecef*)this)->longitude(); }
    inline const Value &height()    const { return ((const Ecef*)this)->height(); }
};


enum AngleUnits
{
    RADIANTS = 0,
    DEGREES,

    NUM_ANGLE_UNITS
};

double AngleFactors[NUM_ANGLE_UNITS] = {
    1,
    180/M_PI
};

template<class PRECISION, AngleUnits UNIT = RADIANTS>
class Angle
{
public:
    typedef PRECISION Value;

    static AngleUnits unitType() { return UNIT; }
    static Value unitFactor() { return AngleFactors[UNIT]; }

    Angle():
        _angle(0)
    {}

    Angle(Value angle):
        _angle(angle)
    {}

    template<class T>
    Angle(const T &angle):
        _angle(angle.value() * unitFactor() / T::unitFactor())
    {}

    template<class T>
    inline Angle &operator=(const T &angle)
    {
        _angle = angle.value() * unitFactor() / T::unitFactor();
        return (*this);
    }

    template<>
    inline Angle &operator=(const Angle<PRECISION,UNIT> &angle)
    {
        _angle = angle.value();
        return (*this);
    }

    inline Value value() const { return _angle; }

private:
    Value _angle;
};

template<class PRECISION>
using Radiants = Angle<PRECISION, RADIANTS>;

template<class PRECISION>
using Degrees = Angle<PRECISION, RADIANTS>;