    #include <iostream>
    #include <vector>
    
    struct Position {};
    
    class Object
    {
    protected:
      Position myPosition;
    
    public:
      Object() {}
      virtual ~Object() {}
    };
    
    class Collidable
    {
    protected:
      /* ... */
    
    public:
      virtual void Collide() = 0;
    
    };
    
    class Grass : public Object
    {
    private:
      /* ... */
    
    public:
    
      Grass() {}
      virtual ~Grass() {}
    };
    
    class Wall : public Object, public Collidable
    {
    private:
      /* ... */
    
    public:
      virtual void Collide() { std::cout << "Wall" << std::endl; }
    
      Wall() {}
      virtual ~Wall() {}
    };
    
    class Monster : public Object, public Collidable
    {
    private:
      /* ... */
    
    public:
      virtual void Collide() { std::cout << "Monster" << std::endl; }
    
      Monster() {}
      virtual ~Monster() {}
    };
    
    int main()
    {
      std::vector<Object*> objects{ new Monster(), new Wall(), new Grass() };
    
      for (auto i : objects){
        if (dynamic_cast<Collidable*>(i)) dynamic_cast<Collidable*>(i)->Collide();
      }
    }
