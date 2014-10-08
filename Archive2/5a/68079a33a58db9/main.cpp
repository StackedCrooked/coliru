#define CHAR_ARRAY(MAX_LENGTH) struct {char data[MAX_LENGTH]; int length;}

struct data {
    CHAR_ARRAY(4) a;
    CHAR_ARRAY(8) b;
};

int main() {
    struct data x = {{{0}, 0}, {{0}, 0}};
    (void) x;
}
