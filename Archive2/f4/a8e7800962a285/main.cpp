#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <functional>
#include <chrono>
#include <fstream>

template<typename RT>
class Point 
{
    std::array<RT,3> data; 
    
    public: 

        Point() = default;

        Point(std::initializer_list<RT>& ilist)
            :
                data(ilist)
        {}

        Point(RT x, RT y, RT z)
            :
                data({x,y,z})
        {};

        RT& operator[](int i)
        {
            return data[i];  
        }

        RT operator[](int i) const
        {
            return data[i];
        }

        const Point& operator += (Point const& other)
        {
            data[0] += other.data[0];
            data[1] += other.data[1];
            data[2] += other.data[2];

            return *this; 
        }

        const Point& operator /= (RT const& s)
        {
            data[0] /= s; 
            data[1] /= s;  
            data[2] /= s;  

            return *this;
        }

};

template<typename RT>
Point<RT> operator-(const Point<RT>& p1, const Point<RT>& p2)
{
    return Point<RT>(p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2]);
}

template<typename RT>
std::ostream& operator<<(std::ostream& os , Point<RT> const& p)
{
    os << p[0] << " " << p[1] << " " << p[2]; 
    return os;
}

template<typename Point>
class Triangle 
{
    std::array<Point, 3> points; 

    public: 

        typedef typename std::array<Point, 3>::value_type value_type;
        
        typedef Point PointType; 

        Triangle() = default; 

        Triangle(std::initializer_list<Point>& ilist) 
            :
                points(ilist)
        {}

        Triangle(Point const& p1, Point const& p2, Point const& p3)
            :
                points({p1, p2, p3})
        {}

        Point& operator[](int i)
        {
            return points[i]; 
        }

        Point operator[](int i) const
        {
            return points[i]; 
        }

        auto begin()
        {
            return points.begin(); 
        }

        const auto begin() const
        {
            return points.begin(); 
        }

        auto end()
        {
            return points.end(); 
        }

        const auto end() const
        {
            return points.end(); 
        }
};

template<typename Triangle>
typename Triangle::PointType barycenter_for(Triangle const& triangle)
{
    typename Triangle::value_type barycenter; 

    for (const auto& point : triangle)
    {
        barycenter += point; 
    }

    barycenter /= 3.; 

    return barycenter; 
}

template<typename Triangle>
typename Triangle::PointType barycenter_unrolled(Triangle const& triangle)
{
    typename Triangle::PointType barycenter; 

    barycenter += triangle[0]; 
    barycenter += triangle[1]; 
    barycenter += triangle[2]; 

    barycenter /= 3.; 

    return barycenter; 
}

template<typename TriangleSequence>
typename TriangleSequence::value_type::value_type
barycenter(
    TriangleSequence const& triangles, 
    std::function
    <
        typename TriangleSequence::value_type::value_type (
            typename TriangleSequence::value_type const &
         )
    > triangle_barycenter 
)
{
    typename TriangleSequence::value_type::value_type barycenter; 

    for(const auto& triangle : triangles)
    {
        barycenter += triangle_barycenter(triangle); 
    }

    barycenter /= double(triangles.size()); 

    return barycenter; 
}

using namespace std;

int main(int argc, const char *argv[])
{
    typedef Point<double> point; 
    typedef Triangle<point> triangle; 

    unsigned int MAX_TRIANGLES = 0;  

    ofstream outFile; 
    outFile.open("results.dat"); 

    for (int exp = 0; exp < 7; ++exp)
    {  
        MAX_TRIANGLES = pow(10, exp);

        typedef std::vector<triangle> triangleVector; 

        triangleVector triangles;

        std::random_device rd;
        std::default_random_engine e(rd());
        std::uniform_real_distribution<double> dist(-10,10); 

        for (unsigned int i = 0; i < MAX_TRIANGLES; ++i)
        {
            triangles.push_back(
                triangle(
                    point(dist(e), dist(e), dist(e)),
                    point(dist(e), dist(e), dist(e)),
                    point(dist(e), dist(e), dist(e))
                )
            );
        }

        typedef std::chrono::high_resolution_clock Clock; 

        auto start = Clock::now();
        auto trianglesBarycenter = barycenter(triangles, [](const triangle& tri){return barycenter_for(tri);});
        auto end = Clock::now(); 

        auto forLoop = end - start; 

        start = Clock::now();
        auto trianglesBarycenterUnrolled = barycenter(triangles, [](const triangle& tri){return barycenter_unrolled(tri);});
        end = Clock::now(); 

        auto unrolledLoop = end - start; 

        cout << "Barycenter difference (should be a zero vector): " << trianglesBarycenter - trianglesBarycenterUnrolled << endl;

        outFile << MAX_TRIANGLES << " " << forLoop.count() << " " << unrolledLoop.count() << "\n"; 
    }

    outFile.close();

    return 0;
}
