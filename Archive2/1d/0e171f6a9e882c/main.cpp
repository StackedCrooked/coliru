template<typename T, 
         unsigned int blockInitSize, 
         unsigned int blockMaxSize>
struct BAInternalIndex;

template<typename T,
         unsigned int blockInitSize, 
         unsigned int blockMaxSize,
         BAInternalIndex<T, blockInitSize, blockMaxSize>* (&getIndexPointer) (const T&)>
class BARef;

template<typename T, 
         unsigned int blockInitSize, 
         unsigned int blockMaxSize>
struct BAInternalIndex
{
    template<typename T2, 
             unsigned int blockInitSize2, 
             unsigned int blockMaxSize2,
             BAInternalIndex<T2, blockInitSize2, blockMaxSize2>* (&getIndexPointer2) (const T2&)>
    friend class BARef;
};

int main()
{
    BAInternalIndex<int, 0, 0> a;
}
