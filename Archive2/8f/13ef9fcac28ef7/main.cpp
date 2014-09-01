#include <cmath>
#include <algorithm>

struct point3d {
    double x,y,z;
    
    point3d()=default;
    point3d(const point3d&rhs)=default;
    point3d&operator=(const point3d&rhs)=default;
    point3d(double x,double y,double z):x(x),y(y),z(z){}
    point3d& operator+=(point3d rhs) {x+=rhs.x;y+=rhs.y;z+=rhs.z;return *this;}
    point3d& operator-=(point3d rhs) {x-=rhs.x;y-=rhs.y;z-=rhs.z;return *this;}
    point3d& operator*=(point3d rhs) {x*=rhs.x;y*=rhs.y;z*=rhs.z;return *this;}
    point3d& operator/=(point3d rhs) {x/=rhs.x;y/=rhs.y;z/=rhs.z;return *this;}
    point3d& operator*=(double rhs) {x*=rhs;y*=rhs;z*=rhs;return *this;}
    point3d& operator/=(double rhs) {x/=rhs;y/=rhs;z/=rhs;return *this;}
    friend point3d operator+(point3d lhs,point3d rhs){return lhs+=rhs;}
    friend point3d operator-(point3d lhs,point3d rhs){return lhs-=rhs;}
    friend point3d operator*(point3d lhs,point3d rhs){return lhs*=rhs;}
    friend point3d operator/(point3d lhs,point3d rhs){return lhs/=rhs;}
    friend point3d operator*(point3d lhs,double rhs){return lhs*=rhs;}
    friend point3d operator/(point3d lhs,double rhs){return lhs/=rhs;}
    friend point3d operator*(double lhs,point3d rhs){return rhs*=lhs;}
    friend point3d operator/(double lhs,point3d rhs){return rhs/=lhs;}
    friend point3d abs(point3d rhs) {return {fabs(rhs.x),fabs(rhs.y),fabs(rhs.z)};}
};

point3d get_intersection(point3d topfrontleft, point3d backbottomright, point3d source)
{
    //find the middle
    point3d middle(topfrontleft.x/2+backbottomright.x/2,
                   topfrontleft.y/2+backbottomright.y/2,
                   topfrontleft.z/2+backbottomright.z/2);
    //slide box and source as if the "middle" was at the origin
    topfrontleft -= middle;
    backbottomright-= middle;
    source -= middle;
    //scale source as if the box is the unit square
    source /= topfrontleft;
    //find the smallest magnatude of the source offset
    point3d mag = abs(source);
    auto min = std::min(mag.x,std::min(mag.y,mag.z));
    //scale the source so that it touches the box
    source /= min;
    //then scale and slide that touching point back to original coordinates
    source = source * topfrontleft + middle;
    return source;
}

int main() {
    
}