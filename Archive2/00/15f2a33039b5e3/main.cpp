struct B {};
struct Coords {};
struct COORDSTYPE {};

template <int DIM>
class A : public B
{

    public:

        template <class T>
        T getValue(void* ptr, int posIdx);

        template <class T>
        T getValue(void* ptr, int posIdx, int valIdx);

        template <class T>
        T getValue(void* ptr, Coords& coord, Coords& size, int valIdx);

        template <class T>
        void setValue(void* ptr, int posIdx, T val);

        template <class T>
        void setValue(void* ptr, int posIdx, int valIdx, T val);

        template <class T>
        void setValue(void* ptr, COORDSTYPE& coord, COORDSTYPE& size, int valIdx, T val);

};

int main() {}