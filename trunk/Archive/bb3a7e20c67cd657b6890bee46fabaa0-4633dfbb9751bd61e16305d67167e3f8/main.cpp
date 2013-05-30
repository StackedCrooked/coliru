template<class... Ts>
struct make_zero_t{
    template<Ts...>
    struct zero_t{};
};

int main(){
    make_zero_t<>::zero_t<> zt;
}