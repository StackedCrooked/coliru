
namespace sob {

template<std::size_t R, std::size_t C>
class snake {
public:
    explicit snake(typename sob::bitboard<R, C>::cell, const sob::bitboard<R, C>& = sob::bitboard<R, C>());
};

}