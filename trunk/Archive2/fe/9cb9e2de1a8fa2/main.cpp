struct Vector2
{
    float _x;
    float _y;

    template<typename T>
    Vector2(T x, T y)
    {
        _x = static_cast<float>(x);
        _y = static_cast<float>(y);
    }
};


void toto(Vector2 const &)
{
}

int main()
{
    Vector2 v(2.3f, 4.4f);
    Vector2 w(2, 4);
    toto(v);
    toto(w);
}
