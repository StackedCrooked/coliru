INPUT:

Node1:
val: "def"
next: (unknown)

Node2:
val: "abc"
next: (unknown)


OUTPUT:

Node *p = sortPair(node1, node2);

assert(p == node2);
assert(p->val == "abc");
assert(p->next == node1);
assert(p->next->val == "def");
assert(p->next->next == NULL);