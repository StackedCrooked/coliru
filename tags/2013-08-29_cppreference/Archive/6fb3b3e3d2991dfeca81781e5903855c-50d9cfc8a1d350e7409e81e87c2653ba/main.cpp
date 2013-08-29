template<int I, void (*O)(void)>
struct operation {
    enum {
        id = I
    };
    typedef void (*fct)(void);
    static const fct ptr;
};

template <int I, void (*O)(void)>
const typename operation<I, O>::fct operation<I, O>::ptr = O;

int main () {
    
}