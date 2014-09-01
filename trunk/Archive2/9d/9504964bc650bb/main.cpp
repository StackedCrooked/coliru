#include <cmath>
#include <algorithm>
#include <iostream>

struct point3d {
    double x,y,z;
    
    point3d()=default;
    point3d(const point3d&rhs)=default;
    point3d&operator=(const point3d&rhs)=default;
    point3d(double x,double y,double z):x(x),y(y),z(z){}
    point3d& operator+=(const point3d& rhs) {x+=rhs.x;y+=rhs.y;z+=rhs.z;return *this;}
    point3d& operator-=(const point3d& rhs) {x-=rhs.x;y-=rhs.y;z-=rhs.z;return *this;}
    point3d& operator*=(const point3d& rhs) {x*=rhs.x;y*=rhs.y;z*=rhs.z;return *this;}
    point3d& operator/=(const point3d& rhs) {x/=rhs.x;y/=rhs.y;z/=rhs.z;return *this;}
    point3d& operator*=(double rhs) {x*=rhs;y*=rhs;z*=rhs;return *this;}
    point3d& operator/=(double rhs) {x/=rhs;y/=rhs;z/=rhs;return *this;}
    friend point3d operator+(point3d lhs,const point3d& rhs){return lhs+=rhs;}
    friend point3d operator-(point3d lhs,const point3d& rhs){return lhs-=rhs;}
    friend point3d operator*(point3d lhs,const point3d& rhs){return lhs*=rhs;}
    friend point3d operator/(point3d lhs,const point3d& rhs){return lhs/=rhs;}
    friend point3d operator*(point3d lhs,double rhs){return lhs*=rhs;}
    friend point3d operator/(point3d lhs,double rhs){return lhs/=rhs;}
    friend point3d operator*(double lhs,point3d rhs){return rhs*=lhs;}
    friend point3d abs(const point3d& rhs) {return {fabs(rhs.x),fabs(rhs.y),fabs(rhs.z)};}
    friend std::ostream& operator<<(std::ostream&o, const point3d& rhs) {return o<<rhs.x<<','<<rhs.y<<','<<rhs.z;}
};

point3d find_box_intersect(point3d topfrontleft, point3d backbottomright, point3d externpt)
{
    //find the middle
    point3d middle(topfrontleft/2+backbottomright/2);
    //slide box and externpt as if the "middle" was at the origin
    topfrontleft -= middle;
    externpt -= middle;
    //scale externpt as if the box is the unit square
    externpt /= topfrontleft;
    //find the largest magnatude of the externpt's offset
    point3d mag = abs(externpt);
    auto max = std::max(mag.x,std::max(mag.y,mag.z));
    //if it's inside the box, don't scale
    if (max < 1)
        max = 1;
    //scale the externpt so that it touches the box
    externpt /= max;
    //then scale and slide that touching point back to original coordinates
    externpt = externpt * topfrontleft + middle;
    return externpt;
}

int main() {
    point3d box[2] = {{1,2,-1},{2,4,1}};
    point3d middle(box[0]/2+box[1]/2);
    int i, n = 16;
    for (i = 0; i < n; i++) {
        double theta = 2 * 3.14159 * i / n;
        point3d externpt {middle.x + cos(theta), middle.y + sin(theta), 0};
        point3d touchpt = find_box_intersect(box[0], box[1], externpt);
        std::cout << touchpt << '\n';
    }
    return 0;
}