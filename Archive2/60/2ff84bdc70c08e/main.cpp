struct TypeC {
    struct subtype {
        enum {X};
        static_assert(X != X, "Attempt to access the non-existent subtype of TypeC.");
    };
};

int main() {}