#include <iostream>
#include <string>
#include <vector>

struct Noisy {
    Noisy(Noisy const &) {
        printf("copy ctor\n");
    }
    Noisy(Noisy &&) {
        printf("move ctor\n");
    }
    Noisy() {
        printf("default ctor\n");
    }
    
    void use() {
        printf("ignore\n");
    }
};
void set_name(Noisy noise) {
    printf("sep\n");
    Noisy local( std::move(noise));
    local.use();
}
Noisy get_temp() {
   return {};
}
int main()
{
    
   set_name(get_temp());
}
