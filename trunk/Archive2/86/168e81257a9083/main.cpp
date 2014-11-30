#include <iostream>
#include <memory>
#include <cassert>

struct Base
{
    virtual void f() const = 0;
    virtual ~Base() {std::cout << "~Base()\n";}
};

struct A: public Base
{
    A(){std::cout << "A()\n";}
    virtual void f() const override{std::cout << "A::f\n";}
    virtual ~A() {std::cout << "~A()\n";}
};
struct B: public Base
{
    B(){std::cout << "B()\n";}
    virtual void f() const override{std::cout << "B::f\n";}
    virtual ~B() {std::cout << "~B()\n";}
    size_t i = 0;
};



template <typename ...Types>
class TypeUnion
{
public:
    // Разрешаем создание неинициализированных объектов
    TypeUnion() {};
    // Запретим копирование
    TypeUnion(const TypeUnion &) = delete;
    // Только перемещение
    TypeUnion(TypeUnion &&) = default;

    ~TypeUnion()
    {
        // Проверяем был ли размещен какой-нибудь объект
        // если да, разрушаем его
        if(deleter) deleter(mem);
    }

    // этот метод размещает в "объединении" объект типа T
    // при этом тип T должен быть перечислен среди типов указанных при создании объединения
    // Список аргументов args будет передан конструктору
    template <typename T, typename ...Args>
    void assign(Args&&... args)
    {
        // Проверяем на этапе компиляции возможность создания объекта в "объединении"
        static_assert ( usize, "TypeUnion is empty" );
        static_assert ( same_as<T>(), "Type must be present in the types list " );

        // Проверяем не размещен ли уже какой-то объект в памяти
        // Если размещен, освобождаем память от него.
        if(deleter) deleter(mem);

        // В выделенной памяти создаем объект типа Т
        // Создаем объект, используя точную передачу аргументов
        new(mem) T(std::forward<Args>(args)...);
        
        // эта функция корректно разрушит инстацированный объект
        deleter = freeMem<T>;
    }

    // Получаем указатель на размещенный в "объединении" объект
    template<typename T>
    T* get()
    {
        static_assert ( usize, "TypeUnion is empty" );
        assert ( deleter ); 
        return reinterpret_cast<T*>(mem);
    }

private:
    // функция этого типа будет использована для вызова деструктора
    typedef void (deleter_t)(void *);

    // Вдруг кто то захочет создать TypeUnion с пустым списком типов?
    static constexpr size_t max()
    {
        return 0;
    }
    // вычисляем максимум на этапе компиляции
    static constexpr size_t max(size_t r0)
    {
        return r0;
    }
    template <typename ...R>
    static constexpr size_t max(size_t r0, R... r)
    {
        return ( r0 > max(r...) ? r0 : max(r...) );
    }

    // is_same для нескольких типов
    template <typename T>
    static constexpr bool same_as()
    {
        return max( std::is_same<T, Types>::value... );
    }

    // шаблонная функция используется для разрушения размещенного в памяти объекта
    template<typename T>
    static void freeMem(void *p)
    {
        reinterpret_cast<T*>(p)->T::~T();
    }

    // Вычисляем максимальный размер из содержащихся типов на этапе компиляции
    static constexpr size_t usize = max( sizeof(Types)... );
    

    // Выделяем память, вмещающую объект наиболшего типа
    alignas(usize) char mem[usize];

    deleter_t *deleter = nullptr;
};

class BaseCreator
{
    TypeUnion<A, B> obj;

public:
    BaseCreator(bool x)
    {
        if(x) obj.assign<A>();
        else  obj.assign<B>();
    }

    // Запретим копирование
    BaseCreator(const BaseCreator &) = delete;
    // Только перемещение
    BaseCreator(BaseCreator &&) = default;

    Base* operator->()
    {
        return obj.get<Base>();
    }
};

int main(int argc, char const *argv[])
{
    BaseCreator p(false);
    p->f();

    std::cout << "sizeof(BaseCreator):" << sizeof(BaseCreator) << std::endl;
    std::cout << "sizeof(A):" << sizeof(A) << std::endl;
    std::cout << "sizeof(B):" << sizeof(B) << std::endl;
    return 0;
}