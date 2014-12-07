// BatteryCharge.cpp : Defines the entry point for the console application.
//

#include<iostream>
#include<array>
#include<map>
#include<vector>
#include<type_traits>
#include<algorithm>

template<typename T, typename = typename std::enable_if<std::is_enum<T>::value >::type>
bool isLast(T const& t)
{
    return t == static_cast<T>(static_cast<int>(T::END_OF_LIST) - 1);
}

template<typename T, typename = typename std::enable_if<std::is_enum<T>::value >::type>
bool isFirst(T const& t)
{
	return t == static_cast<T>(0);
}



template<typename T, typename = typename std::enable_if<std::is_enum<T>::value >::type>
T& operator++(T& t)
{
	if (static_cast<int>(t) < static_cast<int>(T::END_OF_LIST) - 1)
	{
		t = static_cast<T>(static_cast<int>(t)+1);
	}
	return t;
}

template<typename T, typename = typename std::enable_if<std::is_enum<T>::value >::type>
T operator++(T& t, int)
{
	auto ret = t;
	++t;
	return ret;	
}


template<typename T, typename = typename std::enable_if<std::is_enum<T>::value >::type>
T& operator--(T& t)
{
	if (static_cast<int>(t) > 0)
	{
		t = static_cast<T>(static_cast<int>(t)-1);
	}
	return t;
}


template<typename T, typename = typename std::enable_if<std::is_enum<T>::value >::type>
T operator--(T& t, int)
{
	auto ret = t;
	--t;
	return ret;
}



const int Nbattery = 2;
const int Nrecharger = 2;
const int Ndischarger = 1;
const int Ntest = 4;

enum struct StateOfCharge
{
	P0=0,
	P50,
	P100,
	END_OF_LIST
};

//screen output
std::ostream& operator<<(std::ostream& os, StateOfCharge const& s)
{
	if(s==StateOfCharge::P0) os << "P0";
	else if (s==StateOfCharge::P50) os << "P50";
	else if (s == StateOfCharge::P100) os << "P100";
	return os;
}


enum struct StateOfRelax
{
	H0=0,
	H6,
	H12,
	H18,
	H24,
	END_OF_LIST
};

//screen output
std::ostream& operator<<(std::ostream& os, StateOfRelax const& s)
{
	if(s==StateOfRelax::H0) os << "H0";
	else if (s == StateOfRelax::H6) os << "H6";
	else if (s == StateOfRelax::H12) os << "H12";
	else if (s == StateOfRelax::H18) os << "H18";
	else if (s == StateOfRelax::H24) os << "H24";
	return os;
}


struct SingleBatteryState
{
	//initialize battery as unfilled
	StateOfCharge SoC;
	StateOfRelax Relax;
	SingleBatteryState(StateOfCharge _SoC = static_cast<StateOfCharge>(0), StateOfRelax _Relax = static_cast<StateOfRelax>(0))
		: SoC(_SoC)
		, Relax(_Relax)
	{}


	//loop over state
	bool increase()
	{
		//try to increase Relax
		if (!isLast(Relax))
		{
			++Relax;
			return true;
		}
		//if not possible, reset Relax
		else if (!isLast(SoC))
		{
			++SoC;
			Relax = static_cast<StateOfRelax>(0);
			return true;
		}

		//no increment possible: reset and return false
		SoC = static_cast<StateOfCharge>(0);
		Relax = static_cast<StateOfRelax>(0);
		return false;
	}
};

std::ostream& operator<<(std::ostream& os, SingleBatteryState const& s)
{
	os << "("<<s.SoC << "," << s.Relax << ")";
	return os;
}


bool operator<(SingleBatteryState const& s1, SingleBatteryState const& s2)
{
	return std::tie(s1.SoC, s1.Relax) < std::tie(s2.SoC, s2.Relax);
}

bool operator==(SingleBatteryState const& s1, SingleBatteryState const& s2)
{
	return std::tie(s1.SoC, s1.Relax) == std::tie(s2.SoC, s2.Relax);
}

//here specify which cases you want to have tested
std::array<SingleBatteryState, Ntest> TestCases = { SingleBatteryState{ StateOfCharge::P50, StateOfRelax::H6 }
												  , SingleBatteryState{ StateOfCharge::P50, StateOfRelax::H24 }
												  , SingleBatteryState{ StateOfCharge::P100, StateOfRelax::H6 }
												  , SingleBatteryState{ StateOfCharge::P100, StateOfRelax::H24 } };


// for a state s (and action MEASURE), return the entry in the array Test
// which has to be set to true
int getTestState(SingleBatteryState const& s)
{
	auto it = std::find(std::begin(TestCases), std::end(TestCases), s);
	return it - std::begin(TestCases);
}


enum struct SingleAction
{
	RELAX = 0,
	RECHARGE,
	MEASURE,
	END_OF_LIST
};

std::ostream& operator<<(std::ostream& os, SingleAction const& a)
{
	if(a== SingleAction::RELAX) os << "RELAX";
	else if (a == SingleAction::RECHARGE) os << "RECHARGE";
	else if (a == SingleAction::MEASURE) os << "MEASURE";

	return os;
}


enum struct TimeOfDay
{
	H0 = 0,
	H6,
	H12,
	H18,
	END_OF_LIST
};

//screen output
std::ostream& operator<<(std::ostream& os, TimeOfDay const& s)
{

	if(s==TimeOfDay::H0) os << "0:00 h";
	else if (s == TimeOfDay::H6) os << "6:00 h";
	else if (s == TimeOfDay::H12) os << "12:00 h";
	else if (s == TimeOfDay::H18) os << "18:00 h";
	return os;
}


struct Action
{
	SingleAction& operator[](int i) { return A[i]; }
	SingleAction const& operator[](int i) const { return A[i]; }
	
	std::array<SingleAction, Nbattery> A{};

	bool increase()
	{
		for (int i = Nbattery - 1; i >= 0; --i)
		{
			if (!isLast(A[i]))
			{
				++A[i];
				return true;
			}
			else
			{
				A[i] = static_cast<SingleAction>(0);
			}		
		}
		return false;
	}
};


//screen output
std::ostream& operator<<(std::ostream& os, Action const& A)
{
	os << "(";
	for (int i = 0; i < Nbattery-1 ; ++i)
	{
		os << A[i] << ",";
	}
	os << A[Nbattery-1] << ")";

	return os;
}



struct State
{
	std::array<bool, Ntest> Test{};
	TimeOfDay T = TimeOfDay::H0;
	std::array<SingleBatteryState, Nbattery> B{};

	State()
	{
		for (int i = 0; i < Ntest; ++i)
		{
			Test[i] = true;
		}
	}

	bool isSingleActionAllowed(SingleAction const& a) const
	{
		if (static_cast<int>(T) == static_cast<int>(TimeOfDay::H0) &&  a != SingleAction::RELAX)
		{
			return false;
		}

		return true;
	}

	bool isActionAllowed(Action const& A) const
	{
		//check whether single action is allowed
		for (int i = 0; i < Nbattery; ++i)
		{
			if (!isSingleActionAllowed(A[i]))
				return false;
		}

		//check whether enough Rechargers and Dischargers are available
		int re = 0;
		int dis = 0;

		for (int i = 0; i < Nbattery; ++i)
		{
			//increase re counter
			if (A[i] == SingleAction::RECHARGE)
			{
				++re;
			}
			//increase dis counter
			else if (A[i] == SingleAction::MEASURE)
			{
				++dis;
			}

			//check whether ressources are exceeded
			if (re>Nrecharger || dis > Ndischarger)
			{
				return false;
			}
		}

		return true;
	}

	//loop over state
	bool increase()
	{
		//increase time
		if (!isLast(T))
		{
			++T;
			return true;
		}
		else
		{
			T = static_cast<TimeOfDay>(0);
		}

		//if not possible, try to increase single battery states
		for (int i = Nbattery-1; i >= 0; --i)
		{
			if (B[i].increase())
			{
				return true;
			}
		}

		//if also not possible, try to increase Test state
		for (int i = Ntest-1; i >=0; --i)
		{
			if (Test[i])
			{
				Test[i] = false;
				return true;
			}
			else
			{
				Test[i] = true;
			}
		}

		return false;
	}


	// given a single action and a single-battery state, calculate the new single-battery state.
	// it is assumed the action is allowed
	SingleBatteryState newState(SingleBatteryState s, SingleAction const& a) const
	{
		if (a == SingleAction::RELAX)
		{
			++s.Relax;
		}
		else if (a == SingleAction::RECHARGE)
		{
			++s.SoC;
			s.Relax = static_cast<StateOfRelax>(0);
		}
		else if (a == SingleAction::MEASURE)
		{
			--s.SoC;
			s.Relax = static_cast<StateOfRelax>(0);
		}
		return s;
	}

	// calculate new complete state while assuming the action s allowed
	State newState(Action const& a) const
	{
		State ret = *this;

		//increase time
		if (isLast(ret.T))
		{
			ret.T = static_cast<TimeOfDay>(0);
		}
		else
		{
			ret.T++;
		}

		//apply single-battery action
		for (int i = 0; i < Nbattery; ++i)
		{
			ret.B[i] = newState(B[i], a[i]);

			// if measurement is performed, set new Test state.
			// measurement is only possible if Soc=50% or 100%
			// and Relax= 6h or 24h
			if (a[i] == SingleAction::MEASURE
				&& (B[i].SoC == StateOfCharge::P50 || B[i].SoC == StateOfCharge::P100)
				&& (B[i].Relax == StateOfRelax::H6 || B[i].Relax == StateOfRelax::H24))
			{
				ret.Test[getTestState(B[i])] = true;
			}
		}
		return ret;
	}

	int cost(Action const& a) const
	{
		if (std::find(std::begin(Test), std::end(Test), false) == std::end(Test))
		{
			return 0;
		}
		return 1;
	}

};

//screen output
std::ostream& operator<<(std::ostream& os, State const& S)
{
	os << "{(";
	for (int i = 0; i < Ntest-1; ++i)
	{
		os << S.Test[i]<<",";
	}
	os << S.Test[Ntest-1] << "),"<<S.T<<",";

	for (int i = 0; i < Nbattery; ++i)
	{
		os << "(" << S.B[i].SoC << "," << S.B[i].Relax<<")";
	}
	os << "}";

	return os;
}

bool operator<(const State& s1, const State& s2)
{
	return std::tie(s1.Test, s1.T, s1.B) < std::tie(s2.Test, s2.T, s2.B);
}




struct BatteryCharger
{
	bool valueIteration()
	{
		// loop over all states with one specified Test state
		State S;

		int maxDiff=0;
		do
		{
			int prevValue = V.find(S)->second;
			int minCost = prevValue;

			// loop over all actions
			// and determine the one with minimal cost
			Action A;
			do
			{
				if (!S.isActionAllowed(A))
				{
					continue;
				}

				auto Snew = S.newState(A);
				int newCost = S.cost(A) + V.find(Snew)->second;

				if (newCost < minCost)
				{
					minCost = newCost;
				}
			}
			while (A.increase());

			V[S] = minCost;

			maxDiff = std::max(maxDiff, std::abs(prevValue - minCost));
		}
		while (S.increase());

		//return true if no changes occur
		return maxDiff!=0;
	}


	void showResults()
	{
		State S;
		do
		{
			auto Aopt = getOptimalAction(S);
			auto Snew = S.newState(Aopt);
			std::cout << S << "   " << Aopt << "   " << Snew << "   " << V[S] << "   " << V.find(Snew)->second << std::endl;
		}
		while (S.increase());
	}

	Action getOptimalAction(State const& S) const
	{
		Action Aopt;
		
		Action A;
		int minCost = std::numeric_limits<int>::max();
		do
		{
			if (!S.isActionAllowed(A))
			{
				continue;
			}

			auto Snew = S.newState(A);
			int newCost = S.cost(A) + V.find(Snew)->second;

			if (newCost < minCost)
			{
				minCost = newCost;
				Aopt = A;
			}
		}
		while (A.increase());

		return Aopt;
	}

	BatteryCharger()
	{
		State S;
		do
		{
			int ad = 0;
			for (int i = 0; i < Ntest; ++i)
			{
				if (!S.Test[i])
					ad += 100;
			}
			V[S] = ad;
		}
		while (S.increase());
	}

	std::map<State, int> V;
};





int main(int argc, char* argv[])
{
	BatteryCharger BC;

	int count = 0;
	while (BC.valueIteration())
	{
		++count;
	};
	std::cout << "Value Iteration converged after " << count << " iterations\n"<<std::endl;

	//start at 6:00 with no tests at all performed
	State S;
	S.Test[0] = false;
	S.Test[1] = false;
	S.Test[2] = false;
	S.Test[3] = false;
	S.T = TimeOfDay::H6;

	//get sequence of optimal actions
	auto Aopt = BC.getOptimalAction(S);
	while (BC.V[S] != 0)
	{
		std::cout << S << "    " << Aopt << "   " << BC.V[S] << std::endl;

		S = S.newState(Aopt);
		Aopt = BC.getOptimalAction(S);
	}
	std::cout << S << "    " << Aopt << "   " << BC.V[S] << std::endl;

	return 0;
}

