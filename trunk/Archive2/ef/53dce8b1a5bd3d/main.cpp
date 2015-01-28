#include <stdexcept>


template<typename T, T min, T max>
struct RangedParameter
{
    RangedParameter() : t(min)
    {
    }
    
    RangedParameter(const T& t) : t(t)
    {
        validate();
    }
    
    operator T() const { return t; }
    
private:
    void validate()
    {
        if (t < min || t > max)
        {
            throw std::logic_error("Invalid parameter.");
        }
    }
    
    T t;
};



int main()
{
    RangedParameter<int, 0, 100> param;
    param = 1;
}
