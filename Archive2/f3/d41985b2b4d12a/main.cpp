
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

/* Interface */

class Value;

class Datatype {

public:

    virtual std::string to_string(Value* value) = 0;

};

class Value {
    
    Datatype* m_type;

public:

    Value(Datatype* type) : m_type(type) { }

    std::string to_string() {
        return m_type->to_string(this);
    }

};

/* Template Implementation */

template <typename T>
class WrapValueImpl : public Value {

    T m_val;

public:

    WrapValueImpl(Datatype* type) : Value(type) { }

    T& get() {
        return m_val;
    }

    static T& get(Value* value) {
        return static_cast<WrapValueImpl*>(value)->get();
    }
    
    static void set(Value* value, const T& other) {
        get(value) = other;
    }

    class Type : public ::Datatype {

    public:

        virtual std::string to_string(Value* value) {
            std::ostringstream stream;
            stream << WrapValueImpl::get(value);
            return stream.str();
        }

    };

};

/* Concrete datatypes */

typedef WrapValueImpl<long long int> IntValue;
typedef WrapValueImpl<long double> DoubleValue;
typedef WrapValueImpl<std::string> StringValue;

typedef std::vector<Value*> ValueArray;
class ArrayValue : public WrapValueImpl<ValueArray> {

public:

    ArrayValue(Datatype* type) : WrapValueImpl<ValueArray>(type) { }

    class Type : public WrapValueImpl<ValueArray>::Type {
      
    public:
    
        virtual std::string to_string(Value* value) {
            std::ostringstream stream;
            stream << "[";

            ValueArray& array = ArrayValue::get(value);
            ValueArray::const_iterator it = array.begin();
            for (; it != array.end(); it++) {
                stream << (*it)->to_string() << ", ";   
            }
            stream << "]";
            return stream.str();
        }

    };

};

#define SHOW_ARRAY 0

int main() {
    #if SHOW_ARRAY
        ArrayValue::Type t;
        ArrayValue v(&t);
    #else
        StringValue::Type t;
        StringValue v(&t);
        StringValue::set(&v, "Hello!!");
    #endif
    std::cout << v.to_string() << "\n";
    std::cout << "Program exit normal.\n";
    return 0;
}

