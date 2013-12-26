template <unsigned int N>
struct compile_time_int {
    enum {num = N};
};

template <unsigned int N>
struct array_wrapper {

    int arr[N];

    template <unsigned int Ind>
    constexpr int const& at(compile_time_int<Ind> const& index) const {
        return arr[index.num];
    }
};

template <unsigned int> struct deliberate_error;

int main() {
    compile_time_int<2> cti;
    constexpr array_wrapper<3> aw;
    //aw.at(cti);
    //deliberate_error<cti.num> my_error1;
    deliberate_error<aw.at(cti)> my_error2;
}