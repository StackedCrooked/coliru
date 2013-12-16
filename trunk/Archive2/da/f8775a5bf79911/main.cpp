enum class ActionStatus { x };

class IExecutable {
public:
    virtual ActionStatus Execute() = 0;
};

class Action : public IExecutable {
    virtual ActionStatus Execute() {
        return ActionStatus::x;
    }
};

class GoTo : public Action {};

int main(int, char*[]) {
    GoTo x;
    return 0;
}