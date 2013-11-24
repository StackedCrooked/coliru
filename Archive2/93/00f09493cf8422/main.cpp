#include <typeindex>
  
template <typename TFx, typename UFx, typename T>
T maybe(bool isthere, T op, TFx fx, UFx defaultgen) {
	if (isthere) {
        return fx(op);
	}
    return defaultgen();
}

template<typename T>
T maybe(bool isthere, T op) {
    return maybe(
        isthere,
        op,
        [] (T const& x) { return x; },
		[] () { return T(); }
    );
}
 
int main() {
    maybe(true, 1);
}
