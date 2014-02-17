enum count {one, two};

template<count>
struct A {};

template<>
struct A<one> {
    template<count> void get();
    template<> char get<one>(); //error: explicit specialization in non-namespace scope 'struct A<(count)0u>'
};

template<> char A<one>::get<one>(); //error: template-id 'get<one>' for 'char A<(count)0u>::get()' does not match any template declaration
template<> int A<one>::get<two>();


template<> char A<one>::get<one>() {}
template<> int A<one>::get<two>() {}

int main() {}