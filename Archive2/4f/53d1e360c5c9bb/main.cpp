template<class T> class mylist;

template <class T>
class mlist {
protected:
  T item;
  mylist<T>* next;
};

template <class T>
class mylist : mlist<T> {
  T item;
  mylist<T>* next;
};

int main() {
  mylist<int> lst;
  (void) lst;
}