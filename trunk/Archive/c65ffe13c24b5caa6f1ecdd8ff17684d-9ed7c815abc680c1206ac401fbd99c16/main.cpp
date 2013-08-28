if (_dir->Instance()->isDebug()) {
    Utils::LogTextWithInt("growing timers size: ", _glo->Instance()->getGrowingTimers().size());
    for (int i=0; i < _glo->Instance()->getGrowingTimers().size(); i++) {
        GrowingTimer _growingTimer = _glo->Instance()->getGrowingTimers().at(i);
        std::cout << "growing timer Field id and plant id: " << _growingTimer.getFieldID() << " - "
                    << _growingTimer.getPlantID() << std::endl;
    }
}

auto& instance = _glo->Instance();
auto& grow_timers = instance->getGrowingTimers();
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
                break;
            }
        }
        if (delete_grow_timer) break;
    }
    if (delete_grow_timer) 
        _gtIterB = grow_timers.erase(_gtIterB);
    else 
        ++_gtIterB;
}