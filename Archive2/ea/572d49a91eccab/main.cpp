template<class... Args, class R>
auto resolve( R (*fun_ptr)( Args... ) ) -> R( *)( Args... ) {
	return fun_ptr;
}

template<class Sig>
Sig* resolve( Sig* fun_ptr ) {
	return fun_ptr;
}

template<class... Args, class R, class C>
auto resolve( R( C::*mem_ptr )( Args... ) ) -> R( C::* )( Args... ) {
	return mem_ptr;
}

int overloaded(int x) {
    return 3;
}

int overloaded(int x, int y) {
    return 7;
}

int overloaded(int x, int y, int z) {
    return 11;
}

int non_overloaded(int x, int y, int z) {
    return 13;
}

int main() {
    // works
    //auto no = resolve(non_overloaded);
    
    // KABOOM
    //auto o1 = resolve<int>(overloaded);
    // OH GOD EXPLODIES
    //auto o2 = resolve<int, int>(overloaded);
    
    // works
    //auto o2sig = resolve<int(int, int)>(overloaded);
    // works
    auto o3 = resolve<int, int, int>(overloaded);
    
    struct {} _ = decltype(o3)();
}
