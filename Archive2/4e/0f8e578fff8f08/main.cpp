#include <iostream>

class Value
{
    private:
        union
        {
            int Integer;
            double Real;
            bool Boolean;
        };

        enum class ValueTypes
        {
           Empty, Integer, Real, Boolean
        };
        ValueTypes valType;

    public:
        Value() : valType(ValueTypes::Empty) {}
        Value(double Val) : valType(ValueTypes::Real) { Real = Val; }
        Value(int Val) : valType(ValueTypes::Integer) { Integer = Val; }
        Value(bool Val) : valType(ValueTypes::Boolean) { Boolean = Val; }

        /* ... */

        friend std::ostream& operator <<(std::ostream& stream, const Value& val);
};

std::ostream &operator <<(std::ostream &os, const Value &val)
{
    switch (val.valType)
    {
        case Value::ValueTypes::Empty:
            os << "[empty]";
            break;
            
        case Value::ValueTypes::Real:
            os << val.Real;
            break;

        case Value::ValueTypes::Integer:
            os << val.Integer;
            break;

        case Value::ValueTypes::Boolean:
            os << (val.Boolean ? "True" : "False");
            break;
    }

    return os;
}

int main()
{
    Value v(2.1);
    std::cout << v;
}