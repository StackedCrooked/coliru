struct Foo;

template <class T> Foo* Create() { return new Foo; }

Foo* MyFoo = Create<int>();

// (A) I expected point of instantiation to be here

struct Foo {};

// (B) But it appears to be here instead

int main() {}