template<class T> struct trait{};

template<class T, typename trait<T>::type = 0>
void vector() {}

int main() {
  vector<int>();
}