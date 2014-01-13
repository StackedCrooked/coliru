struct foo {}; // look ma, no members

bool operator==(foo const&, foo const&) { return false; }

int main() {
    foo a, b;
    return a == b;
}
