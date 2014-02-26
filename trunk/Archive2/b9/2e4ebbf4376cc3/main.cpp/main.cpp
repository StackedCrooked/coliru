//I have some iterator class defined here

template<class T>
class MyContainer
{
public:
typedef T *Iterator;
T *Begin();
T *End();
//...members and methods
};

template<class Container>
class Sort
{
public:
typedef typename Container::Iterator IteratorType;

static void SomeSortAlgorithm(typename Sort<Container>::IteratorType, typename Sort<Container>::IteratorType)
{
//algorithm goes here
}
};

int main() {
    MyContainer<int> arr;
    Sort<MyContainer<int>>::SomeSortAlgorithm(arr.Begin(), arr.End());   
}