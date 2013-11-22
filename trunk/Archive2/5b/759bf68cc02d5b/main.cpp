boost::variant<array_and_length, pointer_and_length> foo(…) { … }

class bar {
public:
    bar(…) : baz(foo(…)) {
        
    }

private:
    boost::variant<array_and_length, pointer_and_length> baz;
};
