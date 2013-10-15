#include <iostream>
#include <string>
#include <set>
#include <deque>
#include <vector>

struct position{
    int x;
    int y;
    int h;
    int count;
    position():x(0), y(0), h(0), count(0) {}
    position(int _x, int _y, int _h, int _count): x(_x), y(_y), h(_h), count(_count) {}
    friend bool operator< (const position& a, const position &b);
};

bool operator< (const position& a, const position &b){
        if (b.h > a.h){
            return true;
        }else if (b.h == a.h && b.x > a.x){
            return true;
        }else if (b.h == a.h && b.x == a.x && b.y > a.y){
            return true;
        }
        return false;
}

int calTime(std::vector<std::vector<std::vector<char> > > game_map, int m, int n, int h){
    std::set<position> known_position;
    std::deque<position> next_move;
    position prince;
    position princess;
    
    for (int i = 0; i < h; i++){
        for (int j = 0; j < m; j++){
            for (int k = 0; k < n; k++){
                if (game_map[j][k][i] == '1'){
                    prince.x = m;
                    prince.y = n;
                    prince.h = i;
                }
                if (game_map[j][k][i] == '2'){
                    princess.x = m;
                    princess.y = n;
                    princess.h = i;
                }
            }
        }
    }
    
    //put prince in next_move/known_positions
    known_position.insert(prince);
    next_move.push_back(prince);
    
    while(next_move.size() > 0){
        position current = next_move.front();
        next_move.pop_front();
        if (current.x == princess.x && current.y == princess.y && current.h == princess.h){
            return current.count;
        }
        //go down if possible
        if (current.h < h-1 && game_map[current.x][current.y][current.h + 1] == '.'){
            position next(current.x, current.y, current.h + 1, current.count + 1);
            known_position.insert(next);
            next_move.push_back(next);
        }
            
        //find out possible movement and add to next_move
        for (int i = -1; i <=1; i++){
            for (int j = -1; j <=1; j++){
                if (i==0 && j==0){
                    continue;
                }
                //skip if out of range
                if (current.x + i < 0 || current.x + i >=m ||
                    current.y + j < 0 || current.y + j >=n){
                        continue;
                }
                //skip if its column
                if (game_map[current.x + i][current.y + j][current.h] == 'o'){
                    continue;
                }
                //skip if already seen
                position next(current.x + i, current.y + j, current.h, current.count + 1);
                std::set<position>::iterator it = known_position.find(next);
                if (it != known_position.end()){
                    continue;
                }
                //add to next/map
                known_position.insert(next);
                next_move.push_back(next);
            }
        }
    }
    return -1;
}

int main()
{
    std::cout << "test1" << std::endl;
}
