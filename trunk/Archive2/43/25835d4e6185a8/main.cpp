#include <string>
#include <iostream>

class Way {
private:
    std::string id;
	std::string name;

public:
	Way() = default;
	Way(const Way& other) = default;

	void SetName(std::string name) { this->name = name; }
	std::string const & GetName() const { return name; }

	void SetId(std::string id) { this->id = id; }
	std::string const & GetId() const { return id; }
};

class AreaDataRepository {
private:
	AreaDataRepository() = default;
	AreaDataRepository(const AreaDataRepository& orig) = default;
	virtual ~AreaDataRepository() = default;

	Way onGoingWay;
public:
	static AreaDataRepository& Instance()
	{
		static AreaDataRepository singleton;
		return singleton;
	}

	void SetOnGoingWay(Way onGoingWay)	{ this->onGoingWay = onGoingWay;  }
	Way const & GetOnGoingWay() const { return onGoingWay; }
};

int main()
{
	Way wayNode;
	wayNode.SetId("123");
	wayNode.SetName("jan");
	AreaDataRepository::Instance().SetOnGoingWay(wayNode);

	std::cout << AreaDataRepository::Instance().GetOnGoingWay().GetId();

	std::cin.get();
	return 0;
}