#define let auto&&

struct lol {
    lol(const lol&) = delete;
    lol& operator=(const lol&) = delete;
};

int main() {
    let x = lol{};
}