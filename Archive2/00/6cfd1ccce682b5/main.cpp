struct lol {
    lol(const lol&) = delete;
    lol& operator=(const lol&) = delete;
};

int main() {
//    auto x = lol{};
    lol l;
}