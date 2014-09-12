template<class T>
struct P{
    void s(){}

	void test(){
		auto g = [&](){
			auto f = [&](){ s(); };
			f();
		};
		g();
	}
};

int main(){
	P<double> p;
	p.test();
}