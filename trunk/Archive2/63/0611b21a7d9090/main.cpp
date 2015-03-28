#include <iostream>
#include <cmath>
#include <memory>
#include <string>
#include <vector>

// pi constant
constexpr double pi = 3.141592653589793;

//templated setter for many types
template <typename T> 
struct Setter {
    T _i;
    Setter(const T & i) : _i(i) {}
    operator T() const {return _i;}
};

//setter for each parameter
struct Name: Setter<std::string> { using Setter::Setter; };
struct Side: Setter<double> { using Setter::Setter; };
struct Radius: Setter<double> { using Setter::Setter; };

struct Figure {
    std::string _name;
    virtual double area() const=0;
    virtual ~Figure() {}
    void set(const Name & n) { _name = n; }
};

struct Circle: Figure {
    double _radius;
    double area() const override { return pi*_radius*_radius; }
    using Figure::set;
    void set(const Radius & n) { _radius = n; }
};

struct Square: Figure {
    double _side;
    double area() const override { return _side*_side; }
    using Figure::set;
    void set(const Side & n)  { _side = n; }
};

struct Scene {
    std::vector<std::unique_ptr<Figure>> v;
    double total_area() const {
        double total=0;
        for (const auto& f : v)
            total += f->area();
        return total;
    }

    //here we go, this is the standard function with recursion
    template<typename T, typename S, typename ...Args>
    void apply(T& t, const S & setter, Args&&... args) {
        t.set(setter);
        apply(t, std::forward<Args>(args)...);
    }

    //this terminates the recursion
    template<typename T, typename S>
    void apply(T& t, const S & setter) {
        t.set(setter);
    }

    //this is for the empty args call
    template<typename T>
    void apply(T&) {
        std::cerr << "Warning: no parameters set for an object" << std::endl;
    }

    //here is the interface function
    template<typename T, typename ...Args>
    Scene& add(Args&&... args ) {
        std::unique_ptr<T> t(new T());
        apply(*t, std::forward<Args>(args)...);
        v.emplace_back(std::move(t));
        return *this;
    }
};

int main() {
    Scene scene;
    scene.add<Circle>(Name("c1"), Radius(1.))
         .add<Square>(Side(10), Name("s2"))
         .add<Circle>();
    std::cout << "Total area: " << scene.total_area() << std::endl;
}
