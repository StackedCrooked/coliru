template <class T>
class OList;

template <class T>
class OListiterator{
    friend class OList<T>::OList;
    typename OList<T>::Node* iiter;
};

template <class T>
class OList{
     friend class OListiterator<T>::OListiterator;
public:
    class Node{
    };
};

int main() {
    OListiterator<int> iter;
    OList<int> olist;
}