#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

using namespace std;

const int numberOfExperiments = 500;
const int totalTasksCount = 1000;
const int tasksPerTest = 60;
std::vector<int> experiments;

class Task
{
public:
    Task(int id = 0)
    	: _id(id), _isSeen(false)
	{ }

	int id() const { return _id; }
	bool isSeen() const { return _isSeen; }
	void seen() { _isSeen = true; }

private:
	int _id;
	bool _isSeen;
};

void experiment(std::vector<Task> tasks)
{
	int testsCount = 0;
    size_t tasksSeen = 0;
	while (tasksSeen < tasks.size())
	{
		std::set<Task*> ids;
		while (ids.size() < tasksPerTest)
            ids.insert(&tasks[rand() % totalTasksCount]);

		for (auto task : ids)
			if(!task->isSeen())
            {
				task->seen();
                tasksSeen++;
            }
        
		++testsCount;
	}
	experiments.push_back(testsCount);
}

int main()
{
	std::vector<Task> tasks;
	for (int i = 0; i < totalTasksCount; i++)
		tasks.emplace_back(i);

	srand(static_cast<unsigned>(time(0))); 
	for (int n = 0; n < numberOfExperiments; n++)
		experiment(tasks);

	double avg = 0.0;
	for (auto val : experiments)
		avg += val;
	avg /= numberOfExperiments;

	std::cout << "Total number of experiments = " << numberOfExperiments << std::endl
			  << "Min number of tests = " << *std::min_element(std::begin(experiments), std::end(experiments)) << std::endl
			  << "Max number of tests = " << *std::max_element(std::begin(experiments), std::end(experiments)) << std::endl
			  << "Average number of tests = " << avg << std::endl;

	return 0;
}
