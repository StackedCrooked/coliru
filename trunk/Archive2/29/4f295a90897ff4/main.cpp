
// Внимание: для понимания всех нюансов читать комментарии в порядке по номерам

#include <iostream>

using namespace std;

class A {
    
    template<typename T>
    struct B {
        struct C {
            void print();
        };
    };
    
    template<typename T>
    void foo();
    
    // 4. Расположения инстранцирования внутри класса для класса и функиции запрещено, поэтому выносим мпециализацию
    // за пределы класса A
    /*
    // error: no function template matches function template specialization 'print'
    template<>
    void A::B<int>::C::print() {
        cout << "ABC_print_int" << endl;
    }
    
    // error: explicit specialization of 'foo' in class scope
    template<>
    void A::foo<int>() {
        cout << "foo" << endl;
    }
    */
    
    public:
    // 1. errors: Дело в том, что вызов методов доджен быть в коде после инстанцирования конкретных типов
    // поэтому разкомментированная реализация A::doPrivate вызывет ошибку
    /*
    void doPrivate() {
        B<int>::C().print(); // error: explicit specialization of 'print' after instantiation
        foo<int>();          // error: explicit specialization of 'foo<int>' after instantiation
    }
    */
    // 2. приходится определять интерфейс функции, а реализацию распогать после инстанцирования B<T>::C() и foo<T>
    void doPrivate();
};

// 5. Вынесенные за пределы класса A специализации  A::B<int>::C::print и A::foo<int>,
// (ВНИМАНИЕ!) расположенные перед их вызовом в A::doPrivate
template<>
void A::B<int>::C::print() {
    cout << "ABC_print_int" << endl;
}

template<>
void A::foo<int>() {
    cout << "foo" << endl;
}

// 3. имплементация функции A::doPrivate, расположенная после инстанцированных A::B<int>::C::print() и A::foo<int>()
void A::doPrivate() {
    B<int>::C().print();
    foo<int>();
}

int main() {
    // пытаемся обратиться к private функционалу
    A().doPrivate();
    
    return 0;
}