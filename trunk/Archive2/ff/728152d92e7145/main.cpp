#include <cstdint>
#include <cstdio>

using bit_t = uint64_t;
constexpr size_t max_bit_cnt = 64;

void print_binary(bit_t input)
{
    char str[65];
    str[64] = '\0';

    for (int offset = 0; offset < 64; offset++) {
        str[63-offset] = ((input >> offset) & 1) ? '1' : '0';
    }
    
    printf("%s\n", str);
}

void a_impl(size_t pop_cnt, size_t total_bit, bit_t intermediate)
{
    if (pop_cnt == 0) {
        print_binary(intermediate);
        return;
    }
    
    for (size_t offset = pop_cnt-1; offset < total_bit; offset++) {
        a_impl(pop_cnt-1, offset, intermediate | 1 << offset);
    }
}

void a(size_t pop_cnt, size_t total_bit)
{
    if (total_bit >= max_bit_cnt || pop_cnt >= total_bit) {
        printf("precondition violationd\n");
        return;
    }
    a_impl(pop_cnt, total_bit, 0);
}

int main() {
    a(3, 10);
}