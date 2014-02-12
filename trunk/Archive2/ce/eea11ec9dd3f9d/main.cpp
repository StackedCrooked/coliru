class GameState {
public:
    virtual void Init() = 0;
    virtual void Cleanup() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleEvents(int) = 0;
    virtual void Update(int) = 0;
    virtual void Draw(int) = 0;

    void ChangeState(int, int) {}

protected:
        GameState() {}
        virtual ~GameState() {}
};

class State_Intro : public GameState {
public:
    void Init() {}
    void Cleanup() {}

    void Pause() {}
    void Resume() {}

    void HandleEvents(int);
    void Update(int);
    void Draw(int);

    static State_Intro* getInstance() {
        return &m_introState;
    }

protected:
    State_Intro() { }
    virtual ~State_Intro();

private:
    static State_Intro m_introState;
};

int main() {
    State_Intro* x = State_Intro::getInstance();
}