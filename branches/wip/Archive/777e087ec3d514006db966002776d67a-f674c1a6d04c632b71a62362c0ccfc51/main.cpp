#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Point3f
{ 
    float x,y,z;
    Point3f(float _x, float _y,float _z)
    : x(_x),y(_y),z(_z)
    {}
    
    Point3f(const Point3f& p)
        :x(p.x),y(p.y),z(p.z)
    {}
    
    Point3f operator-(const Point3f& p) const
    {
        return Point3f(x-p.x,y-p.y,z-p.z);
    }
    Point3f operator+(const Point3f& p) const
    {
        return Point3f(x+p.x,y+p.y,z+p.z);
    }
    Point3f operator*(const Point3f& p) const
    {
        return Point3f(x*p.x,y*p.y,z*p.z);
    }
    Point3f operator/(const float scalar) const
    {
        return Point3f(x/scalar,y/scalar,z/scalar);
    }
    Point3f operator*(const float scalar) const
    {
        return Point3f(x*scalar,y*scalar,z*scalar);
    }
    bool operator==(const Point3f& p) const
    {
        return x == p.x && y == p.y && z == p.z;
    }
    bool isNull()
    {
        return x+y+z == 0;
    }
};

std::ostream& operator<<(std::ostream& os, const Point3f& p)
{
    os << p.x << " " << p.y << " " << p.z <<" " ;
    return os;
}

struct Vector3f
{
    Point3f point;
    
    Vector3f(const Point3f& p)
    : point(p)
    {
    }
    
    Vector3f(const Vector3f& v)
    : point(v.point)
    {}
    
    Vector3f(const Point3f& p0, const Point3f& p1 )
      :point(p1-p0)
    {
        
    }
    
    Vector3f operator-(const Vector3f& p) const
    {
        return Vector3f(point-p.point);
    }
     Vector3f operator+(const Vector3f& p) const
    {
        return Vector3f(point+p.point);
    }
    Vector3f operator*(const Vector3f& p) const
    {
        return Vector3f(point*p.point);
    }
    Vector3f operator/(const float scalar) const
    {
        return Vector3f(point/scalar);
    }
    Vector3f operator*(const float scalar) const
    {
        return Vector3f(point*scalar);
    }
    bool operator==(const Vector3f& v) const
    {
        return point == v.point;
    }
    Vector3f Cross(const Vector3f& v) const
    {
        float x = (point.y*v.point.z - point.z*v.point.y);
        float y = (point.z*v.point.x - point.x*v.point.z);
        float z = (point.x*v.point.y - point.y*v.point.x);
        return Vector3f(Point3f(x,y,z));
    }
    
    void Normalize()
    {
        float mag = std::sqrt((point.x*point.x) + (point.y*point.y) + (point.z*point.z));
        point = point/mag;
    }
    
    float Dot(const Vector3f& vector) const
    {
        return (point.x*vector.point.x + point.y*vector.point.y + point.z*vector.point.z);
    }
    
    bool IsZero()
    {
        return point.isNull();
    }
};

std::ostream& operator<<(std::ostream& os, const Vector3f& p)
{
    os << "(" <<p.point << ")" ;
    return os;
}

struct Line
{
    Vector3f origin;
    Vector3f direction;
    
    Line(const Vector3f& _origin, const Vector3f& _direction)
    :origin(_origin), direction(_direction)
    {}
};

std::ostream& operator<<(std::ostream& os, const Line& p)
{
    os << "(" <<p.origin<<"," << p.direction<< ")" ;
    return os;
}

typedef int Int;
typedef unsigned int UInt;

Line FoundMediatrice(const Vector3f& _origin, const Vector3f& _direction, const Vector3f& _normal)
{
        //Middle point
    const Vector3f middle(_origin+(_direction/2.0f));
    return Line(middle , _direction.Cross(_normal));
}

float DistanceSquared( const Line& line0, const Line& line1, 
                       float& s_c, float& t_c )
{
    Vector3f w0 = line0.origin - line1.origin;
    float a = line0.direction.Dot( line0.direction );
    float b = line0.direction.Dot( line1.direction );
    float c = line1.direction.Dot( line1.direction );
    float d = line0.direction.Dot( w0 );
    float e = line1.direction.Dot( w0 );
    float denom = a*c - b*b;
    if ( denom == 0.0f )
    {
        s_c = 0.0f;
        t_c = e/c;
        Vector3f wc = w0 - line1.direction*t_c;
        return wc.Dot(wc);
    }
    else
    {
        s_c = ((b*e - c*d)/denom);
        t_c = ((a*e - b*d)/denom);
        Vector3f wc = w0 + line0.direction*s_c
                          - line1.direction*t_c;
        return wc.Dot(wc);
    }

}

int main()
{  
    
   Point3f v[7] = {Point3f(-0.5f,1.f,0.f),Point3f(-1.f,0.f,0.f),Point3f(-0.5f,-1.f,0.f),Point3f(0.f,-2.f,0.f),
                                 Point3f(0.5f,-1.f,0.f),Point3f(1.f,0.f,0.f),Point3f(0.f,0.f,0.f)};
   std::vector<Point3f> vertices(v,v+7);

    //index list in CCW
    Int i[7] = {0,1,2,3,4,5,6};
    std::vector<int> index(i,i+7);


    //Loop for triangle test
    for(UInt i=0;i<(index.size()-2);++i)
       for(UInt j=i+1; j<(index.size()-1);++j )
            for(UInt k=j+1; k<(index.size());++k )
            {
                std::cout << index[i] << index[j] << index[k] << "\t";
                //Normal
                Vector3f vectorJK(Vector3f(vertices[k]) - Vector3f(vertices[j]));
                Vector3f vectorJI(Vector3f(vertices[i]) - Vector3f(vertices[j]));
                Vector3f normal(vectorJK.Cross(vectorJI));

                if(!normal.IsZero())
                {
                        std::cout << "ok";
                        //found mediatrice vectorJK
                        Line m1(FoundMediatrice( Vector3f(vertices[j]), vectorJK, normal));
                        //found mediatrice vectorJI
                        Line m2(FoundMediatrice( Vector3f(vertices[j]), vectorJI, normal));
                        
                        std::cout << "  m1 :" << m1;
                        std::cout << "  m2 :" << m2;
                        
                        float d1(0.0f),d2(0.0f);
                        float dist = DistanceSquared(m1,m2,d1,d2);
                        //Collision
                        if(dist == 0.0f)
                        {
                            Vector3f center1(m1.origin + m1.direction * d1);
                            Vector3f center2(m2.origin + m2.direction * d2);
                            //Collision OK
                            if(center1 == center2)
                            {
                                std::cout << " d:" << dist << " d1:" << d1 << " d2:" << d2 << " CENTER:" << center1 << "" << center2 <<std::endl;    
                            }
                        }
                }
                else 
                    std::cout << "bad" << std::endl;
            }
}
