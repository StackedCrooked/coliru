#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;



template <class T>
struct functionality
{
    // API for T assumed:
    // -------------------
    // T& x();
    // T& y();
    // T& z();
    
    protected:
    virtual ~functionality () { }  // virtual just to get rid of warning
    
    public:
    T* self()             { return static_cast<T*>(this); }
    const T* self() const { return static_cast<const T*>(this); }
    
    template <class U>
    T & operator += (const U& p) {
        self()->x() += p.x();
        self()->y() += p.y();
        self()->z() += p.z();
        return *self();
    }

    template <class U>
    T & operator -= (const U& p) {
        self()->x() -= p.x();
        self()->y() -= p.y();
        self()->z() -= p.z();
        return *self();
    }
    
    T & operator *= (double scalar) {
        self()->x() *= scalar;
        self()->y() *= scalar;
        self()->z() *= scalar;
        return *self();
    }
    
    double& operator[] (size_t i) { 
        switch(i) { 
            case 0: return self()->x();
            case 1: return self()->y();
            case 2: return self()->z();
            assert(false); return 0;
        }
    }
    
    double operator[] (size_t i) const { 
        switch(i) { 
            case 0: return self()->x();
            case 1: return self()->y();
            case 2: return self()->z();
            assert(false); return 0;
        }
    }
    
    void print() const
    {
        const T& p = *self();
        //cout << "{ " << p.x() << ", " << p.y() << ", " << p.z() << " }" << endl;
        cout << "{ " << p[0] << ", " << p[1] << ", " << p[2] << " }" << endl;
        //cout << "{ " << self()->x() << ", " << self()->y() << ", " << self()->z() << " }" << endl;
    }
};

struct Point : public functionality<Point>
{
    double pt[3];

    Point (double x, double y, double z) { pt[0]=x;    pt[1]=y;    pt[2]=z;    }
    Point (double x[3])                  { pt[0]=x[0]; pt[1]=x[1]; pt[2]=x[2]; }
    ~Point() { cout << "~Point of "; print(); }
    
    double &x() { return pt[0]; }
    const double &x() const { return pt[0]; }

    double &y() { return pt[1]; }
    const double &y() const { return pt[1]; }
    
    double &z() { return pt[2]; }
    const double &z() const { return pt[2]; }
};

struct PointRef : public functionality<PointRef>
{
    double * const pt;

    explicit PointRef (double some_point[3]) : pt(some_point) {  }
    explicit PointRef (Point &other) : pt(other.pt) { }
    
    PointRef (const PointRef& other ) : pt(other.pt) { }
    
    PointRef& operator=( const PointRef &other ) { 
        x() = other.x();
        y() = other.y();
        z() = other.z();
        return *this;
    }

template<class U>
    PointRef& operator=( const U &other ) { 
        x() = other.x();
        y() = other.y();
        z() = other.z();
        return *this;
    }
    
    ~PointRef() { cout << "~PointRef of "; print(); }
    
    double &x() { return pt[0]; }
    const double &x() const { return pt[0]; }

    double &y() { return pt[1]; }
    const double &y() const { return pt[1]; }
    
    double &z() { return pt[2]; }
    const double &z() const { return pt[2]; }
};


int main()
{
    Point a(1, 2, 3);
    a.print();
    a+=Point(1,2,3);
    a.print();
    
    double x[3] = { 3, 3, 3 };
    
    PointRef b(x);
    b.print();
    b+=a;
    
    b.print();
    cout << x[0] << " " << x[1] << " " << x[2] << endl;
    
    PointRef c(a);
    c+=b;
    c.print();
    a.print();
}