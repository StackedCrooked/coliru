using StateManager = int;
using View = int;

class GameState
{
public:

    StateManager* game;

    virtual void draw(const float dt) =0;
    virtual void update(const float dt) =0;
    virtual void handleInput()=0;

};

class GameStartState:public GameState
{
public:


    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStartState(StateManager* game);


private:

    View view;
};

GameStartState::GameStartState(StateManager* game)
{
    this->game = game;
}

void GameStartState::draw(const float dt){

   this->game = nullptr;
}

void GameStartState::handleInput(){
    this->game = nullptr;
}

void GameStartState::update(const float dt) {
    this->game = nullptr;
}

int main() {}