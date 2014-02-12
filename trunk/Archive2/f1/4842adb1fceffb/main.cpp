template<typename myEnumType>
int foo(const myEnumType&) { return 0; }

int main() {
    typedef enum {AAA, BBB} myEnumType;
    
    myEnumType enum_type_istance;
    int a = foo(enum_type_istance);
}