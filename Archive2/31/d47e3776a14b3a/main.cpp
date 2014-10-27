#include <iostream>
class StateManager;

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

 //   sf::View view;
};



GameStartState::GameStartState(StateManager* game)
{
    this->game = game;
}

void GameStartState::draw(const float dt){

   this->game;
}

void GameStartState::handleInput(){

   game;

   this->game;

}

void GameStartState::update(float) {
}

int main ()
{
   GameStartState* p = new GameStartState (0);
   std::cout << "passed";
}
