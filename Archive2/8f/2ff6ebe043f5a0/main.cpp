template<typename T>
struct OuterTempl
{
    struct InnerTempl;
    InnerTempl inner;
};

// template struct OuterTempl<int>; // Bad - Ill-formed (NDR?)

template<typename T>
struct OuterTempl<T>::InnerTempl {};

template struct OuterTempl<int>; // Fine

int main() {}