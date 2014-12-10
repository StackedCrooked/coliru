struct vector3d
{
    float X, Y, Z;
 
    inline vector3d( void ) {}
    inline vector3d( const float x, const float y, const float z )
    { X = x; Y = y; Z = z; }

    inline vector3d operator + ( const vector3d& A ) const
    { return vector3d( X + A.X, Y + A.Y, Z + A.Z ); }

    inline vector3d operator + ( const float A ) const
    { return vector3d( X + A, Y + A, Z + A ); }

    inline float Dot( const vector3d& A ) const
    { return A.X*X + A.Y*Y + A.Z*Z; }
};


vector3d foo(const vector3d& x, const vector3d& y, const vector3d& z) {
  return x + y + z;
} 