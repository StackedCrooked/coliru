template <int>
struct Lounge {
    Lounge() = default;
    Lounge(Lounge*) {}
    int Members = 0;
};

struct c {
    constexpr int operator++(int) { return 0; }
} C;

struct { struct { void AddRange(int) {} } Members; } room;

int main() {
    Lounge<C++> lounge = new Lounge<C++>;
    room.Members.AddRange(lounge.Members);
}