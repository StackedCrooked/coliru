template<typename T>
struct Array;

template<typename T>
typename Array<T>::Iterator operator+(int, const typename Array<T>::Iterator& it);

template<typename T>
struct Array
{
    struct Iterator
    {
        friend Iterator operator+<>(int, const typename Array<T>::Iterator&);
    };
};

template<typename T>
typename Array<T>::Iterator operator+(int, const typename Array<T>::Iterator& it)
{
    return it;
}

int main() {}