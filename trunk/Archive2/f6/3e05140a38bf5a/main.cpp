struct a {
    typedef a self;
};

struct b : a {
    using a::self;
};


int main() {}