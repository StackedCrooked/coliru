enum class Color { Red, Blue };
enum class Suit  { Hearts, Spades };

int main() {
   bool eq = Color::Red == Suit::Hearts;
   return 0;
}