#include <string>
#include <functional>
#include <iostream>
#include <map>
using namespace std;

class FieldBase {public: virtual string get_data() = 0; };
class Field : public FieldBase { public: string data; virtual string get_data() { return data; } };

class Struct {
public:
    Field f, g;

    typedef std::map<std::string, const FieldBase*> const_fields_t;
    typedef std::map<std::string, FieldBase*> fields_t;

public:
    const_fields_t get_fields() const {
        cout << "const get_fields() called" << endl;
        return const_fields_t { { "f", &f }, { "g", &g } };
   }

   fields_t get_fields() {
        cout << "non-const get_fields() called" << endl;
        auto const_this = static_cast<const Struct*>(this);
        fields_t result;

        for(auto& v : const_this->get_fields()) {
            result[v.first] = const_cast<FieldBase*>(v.second);
        }
        return result;
   }
};

int main ()
{
    Struct a;
    a.f.data = "Hello";
    a.g.data = "World";
    
    Struct::fields_t obj = a.get_fields();
    
    cout << obj["f"]->get_data() << endl;
    cout << obj["g"]->get_data() << endl;
    
}