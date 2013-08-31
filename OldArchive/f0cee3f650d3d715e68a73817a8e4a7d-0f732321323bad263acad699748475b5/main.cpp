template<class T> struct trait{};

template<class T, typename trait<T>::type...>
void vector() {}

int main() {
  vector<int>();
}