struct test {    
    int data;
    
    auto func() -> decltype(data) {}
};


int main() {
	test t;
    t.func();
}