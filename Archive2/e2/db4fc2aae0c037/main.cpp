#include <iostream>
#include <stack>

struct Arb
{
    int value;
    Arb *left, *right;
    Arb(int value): value(value), left(NULL), right(NULL) {}
    ~Arb()
    {
        if (left)
            delete left;
        if (right)
            delete right;
    }
    void print(const std::string &indent = "")
    {
        if (left)
            left->print(indent + "    ");
        std::cout << indent << value << '\n';
        if (right)
            right->print(indent + "    ");
    }
};

template <class Iterator>
Arb *create_arb(Iterator start1, Iterator last1, Iterator start2, Iterator last2)
{
    std::stack<Arb *> s;
    if (start1 == last1)
        return NULL;
    Arb *ret = new Arb(*start1);
    s.push(ret);
    ++start1;
    while (!s.empty() && start2 != last2)
    {
        if (s.top()->value == *start2)
        {
            ++start2, s.pop();
            continue;
        }
        if (start1 == last1)
            return NULL;
        Arb *node = new Arb(*start1), *t = s.top();
        t->left == NULL ? t->left = node : t->right = node;
        s.push(node);
        if (*start1 == *start2)
            s.pop(), ++start2;
        ++start1;
    }
    return ret;
}

int main()
{
    std::cout << "=============================================\n";
    int a[] = {1, 2, 4, 5, 3, 6, 7};
    int b[] = {4, 5, 2, 6, 7, 3, 1};
    Arb *r = create_arb(a, a + 7, b, b + 7);
    if (r)
        r->print();
    delete r;
    std::cout << "=============================================\n";
    int c[] = {1, 2, 3, 4, 5, 14, 16, 17, 15, 6, 7, 8, 9, 10, 12, 13, 11};
    int d[] = {3, 16, 17, 14, 15, 5, 6, 4, 2, 8, 12, 13, 10, 11, 9, 7, 1};
    r = create_arb(c, c + 17, d, d + 17);
    if (r)
        r->print();
    delete r;
    std::cout << "=============================================\n";
    int x[] = {1, 2, 3, 4, 5};
    int y[] = {2, 4, 5, 3, 1};
    r = create_arb(x, x + 5, y, y + 5);
    if (r)
        r->print();
    delete r;
}
