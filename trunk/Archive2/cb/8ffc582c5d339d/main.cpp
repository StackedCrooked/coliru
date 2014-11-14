#include <iostream>
#include <memory>

template <typename Base, typename State>
class Stateable
{
protected:
    std::unique_ptr<State>	m_currentState;
	std::unique_ptr<State>	m_lastState;

public:
	template <typename Func, typename... Args>
	void call(Func f, Args&&... args)
	{
		auto next = ((*m_currentState).*f)(static_cast<Base &>(*this), std::forward<Args>(args)...);

		if (next) {
			// Exit
			m_currentState->onExit(static_cast<Base &>(*this));
			m_lastState = std::move(m_currentState);
			m_currentState = std::move(next);

			// Enter
			m_currentState->onEnter(static_cast<Base &>(*this));
		}
	}

	Stateable(std::unique_ptr<State> def)
		: m_currentState(std::move(def))
	{
	}
};

class Door;

class DoorState {
public:
	virtual void onEnter(Door &) {};
	virtual void onExit(Door &) {};

	virtual std::unique_ptr<DoorState> open(Door &) = 0;
	virtual std::unique_ptr<DoorState> close(Door &) = 0;
};

class DoorStateClosed : public DoorState {
public:
	void onEnter(Door &) override
	{
		puts("CLAC!");
	}

	std::unique_ptr<DoorState> open(Door &)
	{
		puts("Porte impossible à ouvrir!");

		return nullptr;
	}
	
	std::unique_ptr<DoorState> close(Door &)
	{
		puts("Porte déjà fermée!");

		return nullptr;
	}
};

class DoorStateOpened : public DoorState {
public:
	void onEnter(Door &) override
	{
		puts("Grincement...");
	}

	std::unique_ptr<DoorState> open(Door &)
	{
		puts("Porte déjà ouverte!");

		return nullptr;
	}
	
	std::unique_ptr<DoorState> close(Door &)
	{
		return std::make_unique<DoorStateClosed>();
	}
};

class Door : public Stateable<Door, DoorState>
{
public:
	Door()
		: Stateable(std::make_unique<DoorStateOpened>())
	{
	}

	void open()
	{
		call(&DoorState::open);
	}

	void close()
	{
		call(&DoorState::close);
	}
};

int main(void)
{
	Door d;

	d.open();
	d.open();
	d.close();
	d.close();
	d.open();

	return 0;
}