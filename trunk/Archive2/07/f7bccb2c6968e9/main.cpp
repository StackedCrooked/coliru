struct intermediate_t {
    constexpr intermediate_t() {};
};

constexpr intermediate_t intermediate;

struct tribool {
private:
    enum class state {
        true_value, 
        false_value, 
        intermediate_value
    };
    state value = state::intermediate_value;
public:
    constexpr tribool() = default;
    constexpr tribool(bool b): value(b ? state::true_value : state::false_value) {}
    constexpr tribool(intermediate_t): value(state::intermediate_value) {}
};

int main() {
    tribool b = intermediate;
}