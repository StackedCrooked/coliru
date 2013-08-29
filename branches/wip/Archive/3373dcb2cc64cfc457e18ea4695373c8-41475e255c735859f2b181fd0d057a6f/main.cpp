struct SomeClass {};

template <class K, class T>
struct BaseStruct
{ 
       typedef K kType;
       typedef T tType; 

       kType _key;
       tType _element;

       BaseStruct();       
       BaseStruct(kType const& key, tType const& element);
       BaseStruct(BaseStruct&);
};


       template <class K,class T>
       BaseStruct<K,T>::BaseStruct()
       {}

       template <class K,class T>
       BaseStruct<K,T>::BaseStruct(kType const& key, tType const& element)
       { 
         _key=key;
         _element=element;
       }

       template <class K,class T>
       BaseStruct<K,T>::BaseStruct(BaseStruct& BaseStructInstance)
       { 
         _key=BaseStructInstance._key;
         _element=BaseStructInstance._element;
       }

struct DerivedStruct:public BaseStruct<int, SomeClass>
{
    using BaseStruct::BaseStruct;
};


int main(int argc, char *argv[])
{
    DerivedStruct derivedStructInstance;

    derivedStructInstance=DerivedStruct(0,SomeClass());
}