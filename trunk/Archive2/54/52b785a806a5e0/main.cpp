struct safe_bool
{
    bool value;

    explicit safe_bool(bool value): value(value) {}

    explicit operator bool() const { return value; }

    template<typename T>
    safe_bool(T) = delete;
};

struct Logic
{
    explicit Logic(bool) {}

    template<typename T>
    Logic(const T& val): Logic(bool(safe_bool(val))) {}
};

void foo(Logic const & val) {
    // ...
}

int main()
{
    foo(true); // should work
    foo("hello"); // shouldn't work
    foo(15); // shouldn't work
    
    foo(Logic {true}); // should work
    foo(Logic {"hello"}); // should work
    foo(Logic {15}); // should work
}