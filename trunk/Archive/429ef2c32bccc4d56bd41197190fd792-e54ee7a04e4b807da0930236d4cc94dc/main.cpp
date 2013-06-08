template<class T>
class List{
    // Whatever...
public:
    class Iterator;
};

template <class T>
class List<T>::Iterator{
public:
    Iterator& operator++();
};

template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    // Whatever...
    return *this;
}

int main()
{
    List<int>::Iterator i;
    ++i;
}
