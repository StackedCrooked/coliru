#include <iostream>
#include <memory>

struct Shape;
struct Circle;
struct Rectangle;
struct Patatoid;

bool Collide( Circle const &, Circle const & ) { std::cout << "C vs C"<< std::endl; return true; }
bool Collide( Rectangle const &, Rectangle const & ) { std::cout << "R vs R"<< std::endl; return true; }
bool Collide( Patatoid const &, Patatoid const & ) { std::cout << "P vs P"<< std::endl; return true; }
bool Collide( Circle const &, Rectangle const & ) { std::cout << "C vs R"<< std::endl; return true; }
bool Collide( Circle const &, Patatoid const & ) { std::cout << "C vs P"<< std::endl; return true; }
bool Collide( Rectangle const &, Patatoid const & ) { std::cout << "R vs P"<< std::endl; return true; }
bool Collide( Rectangle const &, Circle const & ) { std::cout << "R vs C"<< std::endl; return true; }
bool Collide( Patatoid const &, Circle const & ) { std::cout << "P vs C"<< std::endl; return true; }
bool Collide( Patatoid const &, Rectangle const & ) { std::cout << "P vs R"<< std::endl; return true; }

//=========================

struct ShapeCollider;
struct Shape {
    friend bool Collide( Shape const & a, Shape const & b ) {
        return a.Collide( b );
    }
    virtual bool Collide( Shape const & ) const = 0;
    virtual ShapeCollider const & Collider() const = 0;
};

//=========================

struct ShapeCollider {
    virtual bool operator()( Shape const &, Circle const & ) const = 0;
    virtual bool operator()( Shape const &, Rectangle const & ) const = 0;
    virtual bool operator()( Shape const &, Patatoid const & ) const = 0;
};

//=========================

template < typename shape__ >
struct ConcreteShapeCollider : public ShapeCollider {
    ConcreteShapeCollider() {}
    bool operator()( Shape const & a, Circle const & b) const { return Collide( static_cast<shape__ const &>(a), b ); };
    bool operator()( Shape const & a, Rectangle const & b) const { return Collide( static_cast<shape__ const &>(a), b ); };
    bool operator()( Shape const & a, Patatoid const & b) const { return Collide( static_cast<shape__ const &>(a), b ); };
};

//=========================

struct Circle : public Shape {
    using ConcreteCollider = ConcreteShapeCollider<Circle>;
    bool Collide( Shape const & other ) const override { return other.Collider()( other, *this ); } 
    ConcreteCollider const & Collider() const override { return collider_; }
    static ConcreteCollider const collider_;
};

//=========================

struct Rectangle : public Shape {
    using ConcreteCollider = ConcreteShapeCollider<Rectangle>;
    bool Collide( Shape const & other ) const override { return other.Collider()( other, *this ); } 
    ConcreteCollider const & Collider() const override { return collider_; }
    static ConcreteCollider const collider_;
};

//=========================

struct Patatoid : public Shape {
    using ConcreteCollider = ConcreteShapeCollider<Patatoid>;
    bool Collide( Shape const & other ) const override { return other.Collider()( other, *this ); } 
    ConcreteCollider const & Collider() const override { return collider_; }
    static ConcreteCollider const collider_;
};

//=========================

Circle::ConcreteCollider const Circle::collider_;
Rectangle::ConcreteCollider const Rectangle::collider_;
Patatoid::ConcreteCollider const Patatoid::collider_;

//=========================

int main() {
    auto c = std::unique_ptr<Shape>{ new Circle };
    auto p = std::unique_ptr<Shape>{ new Patatoid };
    auto r = std::unique_ptr<Shape>{ new Rectangle };
    Collide(*c,*c);
    Collide(*r,*r);
    Collide(*p,*p);
    Collide(*c,*r);
    Collide(*c,*p);
    Collide(*r,*c);
    Collide(*r,*p);
    Collide(*p,*c);
    Collide(*p,*r);
}
