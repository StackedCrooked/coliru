auto& instance = _glo->Instance();
auto& grow_timers = instance->getGrowingTimers();
if (instance->isDebug()) {
    Utils::LogTextWithInt("growing timers size: ", _glo->Instance()->getGrowingTimers().size());
    for(auto& grow_timer : grow_timers)
        std::cout << "growing timer Field id and plant id: " << grow_timer.getFieldID() << " - " << grow_timer.getPlantID() << std::endl;
}
for (auto _gtIterB=grow_timers.begin(); _gtIterB!=grow_timers.end();) { 
    bool delete_grow_timer = false;
    for(auto& field : instance->getFields()) {
        if (_gtIterB->getFieldID() != _fIterB->getFieldNumber())
            continue;
        for(auto& plant : field.getPlants()) {
            if (plant.getPlantID() == _pIterB->getPlantID()) {
                Utils::LogText("gt and plant ID's match");
                Utils::LogTextWithInt("Plant ID after matching: ", plant.getPlantID());
                // Wiggle our plant.
                Utils::wiggleNode(plant.getPlantSprite(), 10.0f, 5.0f);
                plant.setPlantStoppedGrowing(true);
                delete_grow_timer = true;
                break; //quit testing this growtimer
            }
        }
        if (delete_grow_timer) break; //quit testing this growtimer if we know it's deleted
    }
    if (delete_grow_timer) 
        _gtIterB = grow_timers.erase(_gtIterB);
    else 
        ++_gtIterB;
}