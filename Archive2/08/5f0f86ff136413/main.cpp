#include <iostream>

struct llist
{   int x;
    struct llist *next;
};

void trash (llist *&first) {
    if (first == nullptr || first->next == nullptr)
        return;
    
    llist *p = first, *s = first->next;
    while (s != nullptr) {
        if (p->x < s->x) {
            p->x = s->x;
            p->next = s->next;
            delete s;
            s = p->next;
        }
        else {
            p = s;
            s = s->next;
        }
    }
}

std::ostream &operator << (std::ostream &oss, const llist *list) {
    while (list != nullptr) {
        oss << list->x << ' ';
        list = list->next;
    }
    return oss;
}



int main(void) {
    llist *test = new llist{4,
                    new llist{6,
                        new llist{3,
                            new llist{56,
                                new llist{23, nullptr}
                            }
                        }
                    }
                };
    
    std::cout << test << std::endl;
	trash(test);
    std::cout << test << std::endl;
	return 0;
}
