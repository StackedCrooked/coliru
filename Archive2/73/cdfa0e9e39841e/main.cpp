template<typename BoolFlagsType>
struct AdvancedDijkstra
{
    template <int direction, typename F>
	static void run(int source, F onSettle);

	template <int direction, typename F, typename G, typename H>
	static void run(int source, F onSettle, G shouldExpandTo, H onEnqueue);
};

template<typename BoolFlagsType>
template <int direction, typename F>
void AdvancedDijkstra<BoolFlagsType>::run(int source, F onSettle)
{
	(void)source;
	onSettle();
}

template<typename BoolFlagsType>
template <int direction, typename F, typename G, typename H>
void AdvancedDijkstra<BoolFlagsType>::run(int source, F onSettle, G shouldExpandTo, H onEnqueue)
{
	(void)source;
	onSettle();
	shouldExpandTo(4);
	onEnqueue(1.0);
}

int main()
{
	AdvancedDijkstra<int>::run<5>(3, [](){});
	AdvancedDijkstra<int>::run<5>(3, [](){}, [](int){}, [](double){});
}