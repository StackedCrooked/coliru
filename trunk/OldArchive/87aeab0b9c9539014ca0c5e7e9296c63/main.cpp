#include <memory>

void * acquire() { return 0; }
void release(void * ) {  }

int main()
{
    using holder = std::unique_ptr<void, decltype(&release)>;
    holder ptr { acquire(), &release };
}