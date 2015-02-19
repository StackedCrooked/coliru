template<class T>
class list {
public:
    list();
private:
    int size;
};


template <class T>
list<T>::list(){
    this->size = 0;
}

int main(){
      list<int>* x = new list<int>();
      list<int> y;
      return 0;
}