list<direction> get_optimal(vector pos, vector food, unsigned x) {
    vector last_pos = pos;
    list<direction> ret;
    for (unsigned i = 0; i < x; ++i) {
        int best_distance = -INT_MAX;
        direction best_dir = direction::none;
        foreach (direction as d) {
            vector next_pos = last_pos + d;
            if (is_wall_or_snake(next_pos)) continue;
            if (best_distance > distance(next_pos, food)) {
                best_distance = distance(next_pos, food);
                best_dir = d;
                last_pos = next_pos;
            }
        }
        ret.push(best_dir);
    }
    return ret;
}