class Game;

class Player{
  public:
    Player( Game * game );
  private:
    Game * game;
};

class Game{
  public:
    Game();
  private:
    Player p1;
    Player p2;
};

Game::Game() : p1(Player(this)), p2(Player(this)){}

Player::Player( Game * game) : game(game){}

int main() {}