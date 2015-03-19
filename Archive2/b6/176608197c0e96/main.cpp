#include <iostream>
#include <memory>
#include <typeinfo>

struct LineOrCircle
{
    bool line;
    
    LineOrCircle(bool is_line) : line(is_line) {}
};

struct Segment { virtual ~Segment(){}};

struct Circle : Segment
{
    Circle(LineOrCircle&) {}
};

struct Line : Segment
{
    Line(LineOrCircle&) {}
};



std::unique_ptr<Segment> Distinguish(LineOrCircle& LoC)
{
    if (LoC.line)
    {
        return std::make_unique<Line>(LoC);
    }
    else
    {
        return std::make_unique<Circle>(LoC);
    }
}

int main()
{
    LineOrCircle A { true };
    LineOrCircle B { false };
    
    auto A_ = Distinguish(A);
    auto B_ = Distinguish(B);
    
    
    std::cout << typeid(*A_.get()).name() << "\n";
    std::cout << typeid(*B_.get()).name() << "\n";
    
}