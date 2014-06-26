template<bool X = false>
struct SubTypeErrorMessage {
    static_assert(X, "Attempt to access the non-existent subtype of TypeC.");
};

struct TypeC {
    typedef SubTypeErrorMessage<> subtype;
};

// Some context which might want to access subtype, but doesn't necessarily do so
template<typename T>
struct SomeContext {
    typedef typename T::subtype subtype;
};


int main() {
    SomeContext<TypeC> x;       // works, as subtype is not accessed yet
    decltype(x)::subtype y;     // prints above error message
}