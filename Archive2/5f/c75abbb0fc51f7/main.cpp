#define first(u, ...) u
#define a(x, y, ...) first y, first x [__VA_ARGS__]

a(a((1,2),(3,4)), a((5,6),(7,8)))

/// Param first
/*
    a(a((1,2),(3,4)), a((5,6),(7,8)))
    a(3, 1, 7, 5)
    first 1, first 3 [7, 5]
*/

/// Standard expansion (~= macro first)
/*
    > a(a((1,2),(3,4)), a((5,6),(7,8)))
        > a((5,6),(7,8))
        > first (7,8), first (5,6) []
        > 7, 5 []
        
        > a((1,2),(3,4))
        > first (3, 4), first (1, 2) []
        > 3, 1 []
    > first 7, 5 [], first 3, 1 [] []
*/

/// Macro first
/*
    a(a((1,2),(3,4)), a((5,6),(7,8)))
    first a((5,6),(7,8)), first a((1,2),(3,4)) []
    first 7, 5 [], first 3, 1 [] []
*/