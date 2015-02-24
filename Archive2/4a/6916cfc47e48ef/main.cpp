#include <string>

struct Value {};

enum class ValueType {Unknown,Boolean,String,Double,Int32,Int64,Uint32,Uint64,};

class Variant {
public:
    Variant() {};
    Variant(double value) { Type = ValueType::Boolean; value_.vBool = value;};
    
    ValueType Type = ValueType::Unknown;

    Variant& operator= (bool value) { Type = ValueType::Boolean; value_.vBool = value; return *this; };
    Variant& operator= (std::string value) { Type = ValueType::String; value_string_ = value; return *this; };
    Variant& operator= (double value) { Type = ValueType::Double; value_.vDouble = value; return *this; };
    Variant& operator= (int32_t value) { Type = ValueType::Int32; value_.vInt32 = value; return *this; };
    Variant& operator= (int64_t value) { Type = ValueType::Int64; value_.vInt64 = value; return *this; };
    Variant& operator= (uint32_t value) { Type = ValueType::Uint32; value_.vUint32 = value; return *this; };
    Variant& operator= (uint64_t value) { Type = ValueType::Uint64; value_.vUint64 = value; return *this; };

public:

    union Any {
        int32_t vInt32;
        int64_t vInt64;
        double vDouble;
        bool vBool;
        uint32_t vUint32;
        uint64_t vUint64;
        Any() : vDouble(0) {};
    } value_;

    std::string value_string_;

};

int main() {
    Variant v1 = 123;
    Variant v2 = v1;   // <--- Here is where it occurs
    fprintf( stdout, "Value %f [%s]", v2.value_.vDouble, v2.value_string_.c_str() );
}