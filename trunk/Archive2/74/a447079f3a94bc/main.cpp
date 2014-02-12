struct id
{
    template<class F>
    F operator()(F p) const { return p; }
};

struct lambda1 {
    template<typename F>
    auto operator() (F &f) const;
};

template<typename F>
struct lambda2 {
    lambda1 const &l1;
    F &f;
    lambda2(lambda1 const &l1, F &f) : l1(l1), f(f) {}

    template<typename X>
    auto operator() (X x) const { return f( l1(f))(x); }
}; 

template<typename F>
auto lambda1::operator() (F &f) const {
    return lambda2<F>(*this, f);
}   //                  ^
    //                  |
    //                  --- there's no syntax to do this inside a lambda.

int main() {
  lambda1 fix;
  id identity;
  auto fixed = fix(identity);
  fixed(42);
}