template<class... Args, class R>
auto resolve( R (*fun_ptr)( Args... ) ) -> R( *)( Args... ) {
	return fun_ptr;
}

template<class Sig>
Sig* resolve( Sig* fun_ptr ) {
	return fun_ptr;
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

int main() {
    // KABOOM
    auto o1 = resolve<int>(overloaded);
    // OH GOD EXPLODIES
    //auto o2 = resolve<int, int>(overloaded);
    
    // Example to show how it's supposed to work: specifying 3-arguments produces 
    // the right pointer type
    //auto o3 = resolve<int, int, int>(overloaded);
    
    //struct {} _ = decltype(o3)();
}
