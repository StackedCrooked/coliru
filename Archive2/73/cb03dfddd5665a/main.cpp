#include <stdio.h>
#include <functional>

namespace sync {
    
FILE* hello(FILE* fp)   { fprintf(fp, "hello "); return fp; }
FILE* world(FILE* fp)   { fprintf(fp, "world "); return fp; }
FILE* newline(FILE* fp) { fprintf(fp, "\n");     return fp; }


void run() 
{
    printf("= sync ================================\n ");
    hello(stdout);
    world(stdout);
    newline(stdout);
    printf("\n");
}

}

namespace async {

typedef std::function<void(FILE*)> callback_t;

void hello(FILE* fp, callback_t callback)
{
    fprintf(fp, "hello ");
    callback(fp);
}

void world(FILE* fp, callback_t callback)
{
    fprintf(fp, "world ");
    callback(fp);
}

void newline(FILE* fp, callback_t callback)
{
    fprintf(fp, "\n");
    callback(fp);
}

void run()
{
    printf("= async ================================\n ");
    hello(stdout, [] (FILE* fp) {
        world(fp, [] (FILE* fp) {
            newline(fp, [] (FILE* fp) {
                (void)fp;
            });
        });
    });
    printf("\n");
}

}

namespace continuation_passing {

auto hello(FILE* fp)
{
    fprintf(fp, "hello ");
    return [=] (auto c) {
        return c(fp);
    };
}

auto world(FILE* fp)
{
    fprintf(fp, "world ");
    return [=] (auto c) {
        return c(fp);
    };
}

auto newline(FILE* fp)
{
    fprintf(fp, "\n");
    return [=] (auto c) {
        return c(fp);
    };
}

void run()
{
    printf("= continuation passing ================================\n ");
    hello(stdout)(world)(newline);
    printf("\n");
}
    
}

namespace monad {

FILE* hello(FILE* fp)   { fprintf(fp, "hello "); return fp; }
FILE* world(FILE* fp)   { fprintf(fp, "world "); return fp; }
FILE* newline(FILE* fp) { fprintf(fp, "\n");     return fp; }

// for type deduction
template <typename T>
struct Terminal
{
    Terminal(T t) : t(t) {}
    
    template <typename U>
    auto operator()(U u) -> decltype(u(std::declval<T>()))
    {
        return u(t);
    }
    
    T t;
};

// helper
template <typename T>
Terminal<T> terminal(T t) { return Terminal<T>(t); }

// for type deduction
template <typename F>
struct Fmap
{
    Fmap(F f) : f(f) {}
    
    template <typename T>
    auto operator()(T t) -> decltype(terminal(std::declval<F>()(t)))
    {
        return terminal(f(t));
    }
    
    F f;
};

// helper
template <typename F>
Fmap<F> fmap(F f) { return Fmap<F>(f); }

void run()
{
    printf("= monad ================================\n ");
    terminal(stdout)(fmap(hello))(fmap(world))(fmap(newline));
}

}

int main()
{
    sync::run();
    async::run();
    continuation_passing::run();
    monad::run();
}
