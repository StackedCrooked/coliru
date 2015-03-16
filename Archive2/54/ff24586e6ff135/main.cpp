template <typename T>
void Grid::drawbug(const vector<T>& vec, const std::string& label, 
                   vector<string>& vertical, 
                   vector<string>& horizontal) 
{
    string empty = "|-|";
    for (vector<T>::iterator it = vec.begin();
            it != vec.end(); ++it) 
    {
        pair<int, int> temp_pos = (*it).getPosition();
        for (j = 0; j < vertical.size(); j++) {
            if (j == temp_pos.first) {
                unsigned int i;
                for (i = 0; i < horizontal.size(); i++)
                    if (i == temp_pos.second) {
                        horizontal.at(i) = label;
                    } else {
                        horizontal.at(i) = empty;
                    }
    
                for (i = 0; i < horizontal.size(); i++)
                    cout << " " << horizontal.at(i);
                cout << endl;
            }
        }
    }
}
    
void Grid::create(const vector<Aphid>& aphidVector, const vector<Ladybug>& ladyVector) 
{
    // ============= Aphid initial draw section ============================
    vector<string> vertical(this->height);
    vector<string> horizontal(this->length);
    drawbug<Aphid>(aphidVector, "|A|", vertical, horizontal};
    drawbug<Ladybug>(ladyVector, "|L|", vertical, horizontal);
}

