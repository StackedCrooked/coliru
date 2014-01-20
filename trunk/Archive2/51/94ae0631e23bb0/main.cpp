template <typename C, typename R>
class Command {
public:
    Command();

private:
void doTheDew() {
    /* ... */
}
};

template <typename C, typename R>
Command<C, R>::Command() {
    doTheDew();
}

template<typename R>
class Command<void, R> {
public:
    Command() {
        this->doTheDew();
    }
};

template<typename C>
class Command<C, void> {
public:
    Command() {
        this->doTheDew();
    }
};

template<>
class Command<void, void> {
public:
    Command() {
        this->doTheDew(); // 1
    }
};

int main()
{
    Command<int,void> c1; // fail
    Command<void,int> c2; // fail
    Command<int,int> c3; // OK
}
