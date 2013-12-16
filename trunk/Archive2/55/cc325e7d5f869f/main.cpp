struct player_mover {
public:

    void read(key k) {
        if (key_map.find(k) != key_map.end()) {
            direction_queue.push_back(key_map[k]);
        }
    }
    
	void map(key k, sob::cell d) {
        key_map[k] = d;
	}
    
	sob::cell operator()(const sob::cell& pos) {
        if (!direction_queue.empty()) {
            current_dir = direction_queue.front();
    	    direction_queue.pop_front();
        }
        return pos + current_dir;
	}

private:

    sob::cell                   current_dir;        // initially (0, 0)
	std::deque<sob::cell>       direction_queue;    // initially empty
    std::map<key, sob::cell>    key_map;            // initially empty
    
};