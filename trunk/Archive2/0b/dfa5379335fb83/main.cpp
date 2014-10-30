class Instrument
{
public:
    Instrument() = default;
    virtual void print() const = 0;
};

template <class parameter> class Equity : public Instrument
{
public:
    Equity() = default;
    virtual void print() const {}
};

int main()
{
    Equity<double> pb;   
}