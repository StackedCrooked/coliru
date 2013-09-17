template<typename T>
struct Nopes {};

template<typename T, typename Nopes<T>::type...>
void f();

int main() {
	f<int>();
}
