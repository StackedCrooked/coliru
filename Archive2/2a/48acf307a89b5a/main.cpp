
#define COLORS(X) \
    X(Red) \
    X(Green) \
    X(Blue)


#define X(c) c,
enum Color { COLORS(X) };
#undef X


#define X(c) #c,
static const char* color_strings[] = { COLORS(X) };
#undef X

