template<int I, void (*O)(void)>
    struct operation {
        enum {
            id = I
        };
        typedef void (*fct)(void);
        static const fct ptr = O;
    };