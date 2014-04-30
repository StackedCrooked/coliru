#include <iostream>
#include <math.h>       /* modf */

using namespace std;

struct Vector{
    Vector(){}
    Vector(double x, double y, double z, double w):
        x(x), y(y), z(z), w(w){}

    inline Vector operator*(const double other) // first arg by value, second by const ref
    {
      return Vector(x * other, y * other, z * other, w * other); // return the result by value
    }

    inline Vector operator-(const Vector other) // first arg by value, second by const ref
    {
      return Vector(x - other.x, y - other.y, z - other.z, w - other.w); // return the result by value
    }

    double x;
    double y;
    double z;
    double w;
};

inline double dot(Vector v1, Vector v2){
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w;
}
inline Vector frac(Vector v){
    double intpart;
   return Vector( modf (v.x , &intpart), modf (v.y , &intpart), modf (v.z , &intpart), modf (v.w , &intpart) );
}

inline double DecodeFloatRGBA( Vector enc )
{
    Vector kDecodeDot(1.0, 1/255.0, 1/65025.0, 1/160581375.0);
    return dot( enc, kDecodeDot );
}

// Encoding/decoding [0..1) floats into 8 bit/channel RGBA. Note that 1.0 will not be encoded properly.
inline Vector EncodeFloatRGBA( double v )
{
    Vector kEncodeMul(1.0, 255.0, 65025.0, 160581375.0);
    double kEncodeBit = 1.0/255.0;
    Vector enc = kEncodeMul * v;
    enc = frac (enc);
    enc = enc - (Vector(enc.y, enc.z, enc.w, enc.w) * kEncodeBit);
    return enc;
}

int main()
{
    Vector in(0.1, 0.2, 0.3, 0.4);

    double decoded = DecodeFloatRGBA(in);
    cout << "decoded : " << decoded << endl;

    Vector encoded = EncodeFloatRGBA(decoded);
    cout << "encoded : " << encoded.x << "," << encoded.y << "," << encoded.z << "," << encoded.w << endl;

    return 0;
}

