struct X{ virtual ~X() noexcept(true){} };

struct Y : X{ ~Y() noexcept(false){} };

int main(){}