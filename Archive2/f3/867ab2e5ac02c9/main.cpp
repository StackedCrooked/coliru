// from
DO(monad,
    (x, unit(1))
    (y, unit(2))
    (z, unit(3))
    (_, unit(x + y + z))
)
// to
unit(1) >>= [=](auto x) {
    return unit(2) >>= [=](auto y) {
        return unit(3) >>= [=](auto z) {
            return unit(x + y + z)
        };
    };
};