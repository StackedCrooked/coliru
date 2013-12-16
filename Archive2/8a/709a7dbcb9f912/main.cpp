#include <stdio.h>
#include <stdlib.h>

struct tod {
    int h;
    int m;
};

struct event {
    struct tod s;
    struct tod e;
};

int eventCmp(const void *a, const void *b) {
    const struct event *e1 = a;
    const struct event *e2 = b;
    
    if (e1->s.h != e2->s.h) return e1->s.h - e2->s.h;
    return e1->s.m - e2->s.m;
}

void eventPrint(struct event e) {
    printf("%02d:%02d - %02d:%02d\n", e.s.h, e.s.m, e.e.h, e.e.m);   
}

int main(void) {
    int i;
    
    struct event events[] = {
        {{15,  0}, {16, 30}},
        {{ 9,  0}, { 9, 15}},
        {{13,  0}, {14, 20}},
        {{17, 15}, {18,  0}},
    };
    
    qsort(events, 4, sizeof *events, eventCmp);
    
    for (i = 0; i < 4; ++i) {
        eventPrint(events[i]);
    }
    
    return 0;
}
