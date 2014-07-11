template<typename T>
void destroy(T &o) { o.~T(); }

int main()
{
    int x;
    destroy(x);
}