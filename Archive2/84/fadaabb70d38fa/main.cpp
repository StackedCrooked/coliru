template<typename T>
bool isEqual(const T &v0, const T &v1)
{
    return v0 == v1;
}


int main()
{
    enum Enum
    {
        E1,
        E2,
        E3
    } v1, v2;

    v1 = E1;
    v2 = E1;

    isEqual(v1, v2);

}