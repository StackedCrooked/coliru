/* In this example, I have inserted prints to the to_string() methods of
 * the nested Type classes of the WrapValueImpl and TestValue class (where
 * the latter is a subclass of the former and overrides the nested Type
 * class.
 *
 * It shows how the compiler (correctly) uses the _newer_ definition of the
 * nested Type class. However, as you can see in 
 *
 *     http://coliru.stacked-crooked.com/a/f3d41985b2b4d12a
 *
 * it still complains as if it was using the origin implementation of the
 * nested Type class. */


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
            std::cout << "WrapValueImpl::Type::to_string() [we do not want to see this!]\n";
            
            std::ostringstream stream;
            stream << WrapValueImpl::get(value);
            return stream.str();
        }

    };

};

/* Concrete datatypes */

typedef std::vector<Value*> ValueArray;

class TestValue : public WrapValueImpl<int> {

public:

    TestValue(Datatype* type) : WrapValueImpl<int>(type) { }

    class Type : public WrapValueImpl<int>::Type {
      
    public:
    
        virtual std::string to_string(Value* value) {
            std::cout << "TestValue::Type::to_string() [this is the expected print]\n";
            return "42";
        }

    };

};

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
        TestValue::Type t;
        TestValue v(&t);
    #endif
    std::cout << v.to_string() << "\n";
    std::cout << "Program exit normal.\n";
    return 0;
}

