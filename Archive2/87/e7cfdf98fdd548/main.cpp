template <typename T> struct myclass {};

template <typename T> myclass<T>   make_myclass() { return myclass<T>(); }
template <int V>      myclass<int> make_myclass() { return myclass<int>(); }

int main(int argc, char** argv)
{
    auto a = make_myclass<float>();
    auto b = make_myclass<42>();
}