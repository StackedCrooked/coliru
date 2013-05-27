struct test {    
    auto func() -> decltype(data) {}
    
    int data;
};


int main() {
	test t;
    t.func();
}