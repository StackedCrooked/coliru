template <typename T>
T&& forward(typename std::remove_reference<T>::type&& t)
{
    return static_cast<T>(t);
}