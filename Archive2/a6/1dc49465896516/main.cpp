
struct Position
{
    sf::Vector2f position;
}

struct Moving
{
	Position& positionComponent;
	float speed;
	MovingTurret(Position& positionComponent, float speed)
		: positionComponent(positionComponent), speed(speed)
	{
	}
	void update()
	{
		// do Moving-specific update, modify position etc
	}
};


class Turret
{
	Position& positionComponent;

	int size;
	bool canShoot;
	int shotsPerSecond;
	sf::Clock clock;

	void shoot(sf::Vector2f target, std::vector<Bullet> & bullets);

public:
	Turret(Position& positionComponent, int size, int shotsPerSecond)
		: positionComponent(positionComponent), size(size), canShoot(false), shotsPerSecond(shotsPerSecond)
	{
	}

	bool update(sf::Vector2f target, std::vector<Bullet> & bullets, BlockGrid & grid)
	{
		if (target == sf::Vector2f(0, 0))
			return false;

		// do Turret update, call shoot etc
		return true;
	}

	void draw(sf::RenderTarget & target)
	{
		static sf::RectangleShape rectangle(sf::Vector2f(size, size));

		rectangle.setFillColor(sf::Color(255, 255, 0));

		rectangle.setOrigin(rectangle.getSize().x/2, rectangle.getSize().y/2);

		rectangle.setPosition(positionComponent.position);

		target.draw(rectangle);
	}
};


class MovingTurret
{
	Position positionComponent;
	Moving movingComponent;
	Turret turretComponent;
	
 public:
	MovingTurret(sf::Vector2f position, float speed, int shotsPerSecond)
		: position(position), movingComponent(positionComponent, speed), turretComponent(positionComponent, 10, shotsPerSecond)
	{
 
	}
 
	void update()
	{
		if(!turret.update())
		{
			return;
		}
 
		moving.update();
	}
    
    void draw(sf::RenderTarget & target)
	{
        turret.draw(target);
	}
};

