#define first(u, ...) u
#define a(x, y) first y, first x

a(a((1,2),(3,4)), a((5,6),(7,8)))

/// Param first
/*
    a(a((1,2),(3,4)), a((5,6),(7,8)))
    a(3, 1, 7, 5)                       <-- error, 4 params
*/

/// Macro first
/*
    a(a((1,2),(3,4)), a((5,6),(7,8)))
    first a((5,6),(7,8)), first a((1,2),(3,4))
    first 7, 5, first 3, 1
*/