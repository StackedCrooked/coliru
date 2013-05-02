template<typename T,typename D>
D roulette_cast(const T& yey)
{
    static int i = 0;
	if(++i>4) i = 0;

	switch (i)
	{
	case 1:
		return static_cast<D>(yey);
		break;
	case 2:
		return reinterpret_cast<D>(yey);
		break;
	case 3:
		return dynamic_cast<D>(yey);
		break;
	case 4:
		return (D)nullptr;
		break;
	}
}