template<unsigned... Is> struct seq{};
template<unsigned N, unsigned... Is>
struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

#include <array>

using Type = uint8_t;

using Table = std::array<Type, 768>;

constexpr Type red(Type c) {
    return (c % 6 == 0 || c % 6 == 1) ? c : (c % 6 == 2 || c % 6 == 4) ? 255 : 0;
}
constexpr Type green(Type c) {
    return (c % 6 == 2 || c % 6 == 3) ? c : (c % 6 == 0 || c % 6 == 5) ? 255 : 0;
}
constexpr Type blue(Type c) {
    return (c % 6 == 4 || c % 6 == 5) ? c : (c % 6 == 1 || c % 6 == 3) ? 255 : 0;
}

template<unsigned... Is>
constexpr Table MagicFunction(seq<Is...>){
    return {{red(Is)..., green(Is)..., blue(Is)...}};
}

#include <iostream>

int main(){
    constexpr Table table = MagicFunction(gen_seq<256>{});
    for (const auto & e : table) {
        std::cout << static_cast<int>(e);
    }
    std::cout << '\n';
    
    std::array<std::array<uint8_t, 256>, 3> overlayColorMap = [](){
        std::array<std::array<uint8_t, 256>, 3> lut;
        //interleaved spectral colors
        for (std::size_t i = 0; i < 256; ++i) {
            lut[0][i] = i;
            lut[1][i] = 255;
            lut[2][i] = 0;
            ++i;
            lut[0][i] = i;
            lut[1][i] = 0;
            lut[2][i] = 255;
            ++i;
            lut[0][i] = 255;
            lut[1][i] = i;
            lut[2][i] = 0;
            ++i;
            lut[0][i] = 0;
            lut[1][i] = i;
            lut[2][i] = 255;
            ++i;
            lut[0][i] = 255;
            lut[1][i] = 0;
            lut[2][i] = i;
            ++i;
            lut[0][i] = 0;
            lut[1][i] = 255;
            lut[2][i] = i;
        }
        return lut;
    }();
    for (const auto & color : overlayColorMap) {
        for (const auto & pixel : color) {
            std::cout << static_cast<int>(pixel);
        }
    }
}