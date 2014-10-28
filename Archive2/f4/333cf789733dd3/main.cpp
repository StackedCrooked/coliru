class Map;

class Game {

    private:
        Map *map;
        Game* gamePtr;

    public:
        void init(Game* ownPtr);
        int getTestInt();
};

class Game;

class Map {
    private:
        Game* gamePtr;
    public:
        int test();
};

void Game::init(Game* ownPtr) {
    gamePtr = ownPtr;
    map = new Map(gamePtr); // acts as "parent" to refer back (is needed.)
}

int Game::getTestInt() {
    return 5;    
}

int Map::test() {
    return gamePtr->getTestInt();
}

int main()
{
    Game game;
    Game* gamePtr = &game;
    game.init(gamePtr);
    game.gamePtr->map->test();
    
    return 0;
}