// --- proof of concept ---
struct brick {
    brick(int) {}
    brick(brick const&) = delete;
    brick(brick&&) = delete;
    brick& operator=(brick const&) = delete;
    brick& operator=(brick&&) = delete;
};

brick make_brick(int n) {
    return { n };
}
