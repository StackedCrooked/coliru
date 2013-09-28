std::vector<sf::Vector2i> emptyBlocks; 

for (int x = 0; x < grid.getSize().x; ++x) 
    for (int y = 0; y < grid.getSize().y; ++y)
    { 
        if (!grid.isSolid(x, y)) 
            emptyBlocks.push_back(sf::Vector2i(x, y)); 
    } 

    Random random; 

    for (auto block : emptyBlocks) 
        if (random.nextBool() && random.nextBool() && random.nextBool()) 
            turrets.push_back(Turret(sf::Vector2i(block.x, block.y), 5)); 
}