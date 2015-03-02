#include "CEnemyHealth.h"

CEnemyHealth::CEnemyHealth()
{
    
}

void CEnemyHealth::Set(SDL_Renderer* passed_renderer, CEnemy &passed_cenemy)
{
    this->cenemy1 = passed_cenemy;


}


CEnemyHealth::~CEnemyHealth()
{
    //dtor
}
