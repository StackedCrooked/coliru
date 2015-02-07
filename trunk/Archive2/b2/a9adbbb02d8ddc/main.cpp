#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

static const double COST_TO_PLAY = -1.0;
static const double COST_TO_SWITCH = -5.0;
static const double WINNINGS = 20.0;
static const double ODDS_WIN = 1.0/6.0;
static const double ODDS_LOSE = 5.0/6.0;
static const unsigned MAX_DISPLAY = 2;
static const unsigned MAX_CALCULATIONS = 800000;

struct data {
    unsigned long long decisions;
    double odds_right;
    double winnings_right;
    double odds_wrong;
    double winnings_wrong;

    friend bool operator>(const data& left, const data& right) 
    {
        double lefttotal = left.winnings_right+left.winnings_wrong;
        double righttotal = right.winnings_right+right.winnings_wrong;
        if (lefttotal != righttotal)
            return lefttotal > righttotal;
        return left.decisions > right.decisions;
    }

    void display(unsigned turn) {
        for(unsigned i=0; i<=turn; ++i) {
            if ((decisions&(1ull<<i))==0) 
                std::cout << 'C';
            else
                std::cout << 's';
        }
        std::cout << "    " << (winnings_right/2.0 + winnings_wrong/2.0) << '\n';
    }
};

int main() {
    std::vector<data> lastturn;
    std::vector<data> newturn;

    lastturn.push_back({1u, ODDS_LOSE, (WINNINGS+COST_TO_PLAY)*ODDS_WIN, 1.0, COST_TO_PLAY});    
    std::cout<<"0        1         2         3         4         5         6\n";
    std::cout<<"1234567890123456789012345678901234567890123456789012345678901234\n";
    lastturn[0].display(1);

    for(unsigned turn=1; turn<64; ++turn) {

        //if on average you're behind by 20, then you're probably not going to catch up
        double min_winnings = lastturn[0].winnings_right+lastturn[0].winnings_wrong-WINNINGS*ODDS_LOSE;
        newturn.clear();
        if (lastturn.size() > MAX_CALCULATIONS)
            lastturn.resize(MAX_CALCULATIONS);
        newturn.reserve(lastturn.size()*2);

        data cur;
        for(unsigned i=0; i<lastturn.size(); ++i) {
            data& prev = lastturn[i];

            //what happens when we stay
            cur.decisions = prev.decisions | (1ull<<turn);
            cur.odds_right = prev.odds_right * ODDS_LOSE;
            cur.winnings_right = prev.winnings_right + (COST_TO_PLAY + WINNINGS*ODDS_WIN)*prev.odds_right;
            cur.odds_wrong = prev.odds_wrong;
            cur.winnings_wrong = prev.winnings_wrong +(COST_TO_PLAY)*prev.odds_wrong;
            if (cur.winnings_right + cur.winnings_wrong >= min_winnings)
                newturn.push_back(cur);
            
            //what happens when we switch
            cur.decisions = prev.decisions;
            cur.odds_right = prev.odds_wrong * ODDS_LOSE;
            cur.winnings_right = prev.winnings_wrong +(COST_TO_PLAY + COST_TO_SWITCH + WINNINGS*ODDS_WIN)*prev.odds_wrong;
            cur.odds_wrong = prev.odds_right;
            cur.winnings_wrong = prev.winnings_right + (COST_TO_PLAY + COST_TO_SWITCH)*prev.odds_right;
            if (cur.winnings_right + cur.winnings_wrong >= min_winnings)
                newturn.push_back(cur);
        }

        std::sort(newturn.begin(), newturn.end(), std::greater<data>());
        std::cout<<"0        1         2         3         4         5         6\n";
        std::cout<<"1234567890123456789012345678901234567890123456789012345678901234\n";
        for(unsigned i=0; i<newturn.size() && i<MAX_DISPLAY-1; ++i)
            newturn[i].display(turn);
        if (newturn.size() > MAX_DISPLAY)
            std::cout<<"("<<newturn.size()-MAX_DISPLAY<<" elided)\n";
        if (newturn.size() >= MAX_DISPLAY)
            newturn[newturn.size()-1].display(turn);
        

        newturn.swap(lastturn);
    }
    
    return 0;
}