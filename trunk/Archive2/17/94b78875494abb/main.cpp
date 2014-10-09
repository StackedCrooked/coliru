template <class T>
class Graf {
public:
    Graf();
    Graf( int size );
    virtual ~Graf();

    virtual int vartex_count() = 0;
    //other methods
    
    int size;
};


template <class T>
class MGraf : public Graf<T>{
public:
    MGraf();
    MGraf( int size );
    virtual ~MGraf();

    int vartex_count();
    //other methods

};

template<class T> Graf<T>::Graf() {
    this->size = 0;
}

template<class T> Graf<T>::Graf( int size ) {
    this->size = size;
}

template<class T> Graf<T>::~Graf() {
}

template<class T> MGraf<T>::MGraf() : Graf<T>() {}
template<class T> MGraf<T>::MGraf( int size ) : Graf<T>( size ) {}
template<class T> MGraf<T>::~MGraf() {}
template<class T> int MGraf<T>::vartex_count() {return 0;}

int main(int argc, char** argv)
{
    MGraf<void> mg;
    return 0;
}