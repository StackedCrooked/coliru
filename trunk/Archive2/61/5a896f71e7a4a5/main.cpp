template <class T, int odds>
void populate(std::vector<T> &t, BlockGrid &grid) {
    std::vector<sf::Vector2i> emptyBlocks;

	for (int x = 3; x < grid.getSize().x - 4; ++x)
		for (int y = 0; y < grid.getSize().y; ++y)
			if (!grid.isSolid(x, y))
				emptyBlocks.push_back(sf::Vector2i(x, y));

	Random random;

	for (auto block : emptyBlocks)
	if (random.irandom_range(0, odds) == 0) {
		auto bs = grid.getBlocksize() + grid.getBlockSize() / 2;
		t.push_back(T(sf::Vector2f(bs, bs), 1));
	}
}
