#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>

#include <time.h>

struct str {
    char *text;
    size_t size;
};

struct strs {
    struct str *strings;
    size_t size;
    size_t capacity;
};

#define STRS_INIT \
    { 0, 0, 0 }

inline int strs_reserve(struct strs *p, size_t nelements) {
    int r = 1;
    if (nelements > p->capacity) {
        void *pnew = p->strings;
        pnew = realloc(pnew, nelements * sizeof(struct str));
        if (pnew) {
            p->strings = (struct str *)pnew;
            p->capacity = nelements;
            r = 0;
        }
    }
    return r;
}

inline int strs_grow(struct strs *p, size_t nelements) {
    int r = 0;
    if (nelements > p->capacity) {
        size_t new_nelements = p->capacity + p->capacity / 2;
        if (new_nelements < nelements) {
            new_nelements = nelements;
        }
        // 1 2 3 4 6 9 13 19 28 42 63...
        r = strs_reserve(p, new_nelements);
    }
    return r;
}

inline int strs_emplace_back(struct strs *p, const char *text) {
    int r = strs_grow(p, p->size + 1);
    if (r == 0) {
        size_t text_size = strlen(text);
        char *pcopy = (char *)malloc(sizeof(char) * (text_size + 1));
        if (pcopy) {
            memcpy(pcopy, text, text_size + 1);
            struct str *pstr = &(p->strings[p->size]);
            pstr->text = pcopy;
            pstr->size = text_size;
            p->size++;
        } else {
            r = 1;
        }
    }
    return r;
}

constexpr int size = 5000;
char buffer[size] = {};
const std::string buffer2(size - 1, 'A');

void strs_destroy(struct strs *p) {
    for (size_t i = 0; i < p->size; i++) {
        free(p->strings[i].text);
    }
    free(p->strings);
}

void fc() {
    for (int k = 0; k < 1000; k++) {
        struct strs v = STRS_INIT;

        for (int i = 0; i < 1000; i++) {
            strs_emplace_back(&v, buffer);
        }

        strs_destroy(&v);
    }
}

void f() {
    for (int k = 0; k < 1000; k++) {
        std::vector<std::string> v;

        for (int i = 0; i < 1000; i++) {
            v.emplace_back(buffer2);
        }
    }
}

void run_test(const char *message, void (*test)(void)) {
    time_t start = clock();
    test();
    printf("%s %d\n", message, int(clock() - start));
}

int main() {
    for(int i = 0; i < size; ++i)
        buffer[i] = 'A';
    buffer[size-1] = 0;

    run_test("c", &fc);
    run_test("c++", &f);
    return 0;
}