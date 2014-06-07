#include <iostream>

class ClassB;

class ClassA
{
    public:
    ClassA();
    explicit ClassA( const int& num );
    explicit ClassA( const float& num );

    float getNumber();

    private:
    float _number;

};

ClassA::ClassA()
: _number( 0 )
{
    std::cout << "ClassA default constructor\n";
}

ClassA::ClassA( const int& num )
: _number( num )
{
    std::cout << "ClassA int constructor\n";
}

ClassA::ClassA( const float& num )
: _number( num )
{
    std::cout << "ClassA float constructor\n";
}

float
ClassA::getNumber()
{
    return _number;
}

class ClassA;

class ClassB
{
    public:
    explicit ClassB( const int& num );

    explicit operator ClassA() const throw();
    explicit operator int() const throw();
    explicit operator float() const throw();

    int getNumber() const;

    private:
    int _number;
};

ClassB::ClassB( const int& num )
: _number( num )
{
    std::cout<<"ClassB int constructor\n";
}

ClassB::operator ClassA() const throw()
{
    std::cout << "ClassB operator ClassA()\n";
    ClassA newClassA( _number );
    std::cout << "end of ClassB operator ClassA()\n";
    return newClassA;
}

ClassB::operator int() const throw()
{
    std::cout << "ClassB operator int()\n";
    int newInt( _number );
    return newInt;
}

ClassB::operator float() const throw()
{
    std::cout << "ClassB operator float()\n";
    float newFloat( _number );
    return newFloat;
}

int
ClassB::getNumber() const
{
    return _number;
}

int main( int argc, const char* argv[] )
{
    std::cout << "Creating b:\n";
    ClassB b( 5 );
    std::cout << "Casting b to a ClassA:\n";
    ClassA a = static_cast<ClassA>( b );
}