class Numeric
{
public:
    virtual ~Numeric() = 0;
    virtual int getNumeric() const = 0;
};

class Impl : public Numeric 
{
public:
    virtual ~Impl() {}
    virtual int getNumeric() const {return 0;}
};

int main() {
    Impl a;
    a.getNumeric();
}