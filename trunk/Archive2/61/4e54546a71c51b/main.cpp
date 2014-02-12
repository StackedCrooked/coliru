#include <iostream>
#include <type_traits>

template <typename T>
struct is_model {
    private:
        template <typename B, typename A> struct size_t_allowed;
        template <typename B> struct size_t_allowed<B, size_t>{};

        template <typename B, typename A> struct double_allowed;
        template <typename B> struct double_allowed<B, double>{};

        template <typename Z> static auto test(const Z* z) -> decltype(
                size_t_allowed<size_t,decltype(z->getS())>(), 
                size_t_allowed<size_t,decltype(z->getA())>(),
                double_allowed<double,decltype(z->getTransitionProbability(0,0,0))>(),
                double_allowed<double,decltype(z->getExpectedReward(0,0,0))>(),
                std::true_type{} );
        template <typename> static auto test(...) -> std::false_type;
    public:
        enum { value = std::is_same<decltype(test<T>(0)), std::true_type>::value };
};

struct Model {
    size_t getS() const { return 0;}
    size_t getA() const { return 0;}

    double getTransitionProbability(size_t, size_t, size_t) const {return 0.0;}
    double getExpectedReward(size_t, size_t, size_t) const {return 0.0;}
};

template <typename M>
void algorithm(M, typename std::enable_if<is_model<M>::value>::type * = nullptr) {
    std::cout << "Algorithm has been performed.\n";
}

int main() {
    std::cout << is_model<int>::value << "\n";
    std::cout << (is_model<Model>::value ? "Yes" : "No" ) << "\n";
    Model m;
    algorithm(m);

    return 0;
}