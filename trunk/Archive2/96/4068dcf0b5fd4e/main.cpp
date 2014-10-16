template <typename PRIM_TYPE> class WrappedPrimitive
{
    PRIM_TYPE v;

    operator PRIM_TYPE() const { return v; } // same as in your code
    operator PRIM_TYPE&() { return v; }      // non-const reference to wrapped data
};

void maninpulateFloat(float *f) {*f = 5.0f;}

int main() {
    WrappedPrimitive<float> a;
    maninpulateFloat(&a);
}
