#include <iostream>
#include <cstdint>

union P {
    timeval _timeval;
    int8_t  _int8_t;
    uint8_t _uint8_t;

    operator const timeval() const {
        return _timeval;
    }

    operator const int8_t() const {
        return _int8_t;
    }
};


struct Y {

    operator const int8_t() const {
        return static_cast<int8_t>(_p);
    }

    operator const timeval() const {
        return static_cast<timeval>(_p);
    }

    P _p;
};

int main()
{

    Y testobj;
    timeval ret = static_cast<timeval>(testobj);
    return 0;
}
