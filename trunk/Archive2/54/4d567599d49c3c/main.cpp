#include <string>
#include <vector>
#include <thread>

struct TPosition {};

class Robot {
public:
    Robot();
    virtual ~Robot() {};
    TPosition  GetPos() { return mPos; }
    static int mRobotIndex;
    static int GetRobotsCreated();
  private:
    TPosition mPos;

  protected:
    void SetPos();
};

Robot::Robot() {
    mRobotIndex++;
}

int Robot::GetRobotsCreated() {
    return mRobotIndex;
}

int Robot::mRobotIndex=0;

#include <iostream>
#include <mutex>

void threadFunction(int i)
{
    static std::mutex mx;
    std::lock_guard<std::mutex> lk(mx); // take a lock for console output
    std::cout << "Yoohoo from " << i << "\n";
}

int main()
{
    std::array<Robot, 10> robots;

    int const crobotscreated = Robot::GetRobotsCreated();

    std::vector<std::thread> evalThreads(crobotscreated);
    for (int i = 0; i < crobotscreated; ++i)
    {
        evalThreads[i] = std::thread(threadFunction, i);
    }

    for (int i = 0; i < crobotscreated; ++i)
    {
        if (evalThreads[i].joinable())
            evalThreads[i].join();
    }
}
