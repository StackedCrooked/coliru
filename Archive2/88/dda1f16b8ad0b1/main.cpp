struct velocity
{
    float x;
    float y;
};

struct collisionDirection
{
    bool left;
    bool right;
    bool up;
    bool down;
};

class Entity
{
    collisionDirection collisiondirection;
    velocity vel;
};

int main() {}