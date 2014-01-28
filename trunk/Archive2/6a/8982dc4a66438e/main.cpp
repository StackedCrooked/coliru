#include <iostream>
#include <type_traits>
#include <utility>

class has_position {
public:
    double x, y;
};

class has_speed : public virtual has_position {
public:
    double hspeed, vspeed;

    void step() {
        x += hspeed;
        y += vspeed;
    }
};

class has_gravity : public virtual has_speed {
public:
    double gravity;

    void step() {
        if (vspeed > 0.0)
            vspeed /= gravity;
        else if (vspeed == 0.0)
            vspeed = -0.1;
        else
            vspeed *= gravity;
    }
};

class has_friction : public virtual has_speed {
public:
    double friction;

    void step() {
        hspeed /= friction;
        if (hspeed < 0.01 && hspeed > -0.01)
            hspeed = 0.0;

        vspeed /= friction;
        if (vspeed < 0.01 && vspeed > -0.01)
            vspeed = 0.0;
    }
};

template<typename... Bases>
class mixin : public virtual Bases... {
public:
    void step() {
        step_bases<Bases...>();
    }

private:
    template<typename T, typename = void>
    struct has_step : public std::false_type { };
    
    template<typename T>
    struct has_step<T, decltype(std::declval<T>().step())> : public std::true_type { };

    template<
        typename Head,
        typename... Tail
    >
    typename std::enable_if<has_step<Head>::value>::type step_bases() {
        Head::step();
        step_bases<Tail...>();
    }

    template<
        typename Head,
        typename... Tail
    >
    typename std::enable_if<!has_step<Head>::value>::type step_bases() {
        step_bases<Tail...>();
    }

    template<
        typename... List,
        typename = typename std::enable_if<sizeof...(List) == 0>::type
    >
    void step_bases() { }
};

class enemy : public mixin<has_position, has_speed, has_friction, has_gravity> {
public:
};

int main() {
    enemy ghost;
    ghost.x = 0.0;
    ghost.y = 0.0;
    ghost.hspeed = 1.0;
    ghost.vspeed = 4.0;
    ghost.gravity = 1.5;
    ghost.friction = 1.2;

    for (auto i = 0; i < 20; ++i) {
        std::cout << "x = " << ghost.x << "; y = " << ghost.y
                  << "; hspeed = " << ghost.hspeed << "; vspeed = " << ghost.vspeed
                  << '\n';
        ghost.step();
    }

    return 0;
}
