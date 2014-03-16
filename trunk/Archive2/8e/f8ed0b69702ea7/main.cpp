
struct __cook {
        virtual ~__cook() noexcept = default ;
};

struct __cook1: public __cook {
        virtual ~__cook1() noexcept = default;
};

struct __cook2: public __cook {
        virtual ~__cook2() noexcept;
};
__cook2::~__cook2() noexcept {}

struct __cook3: public __cook {
        virtual ~__cook3() noexcept;
};
__cook3::~__cook3() noexcept = default;