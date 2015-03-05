#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <string>

using namespace std;


const char FLOOR = '1' ;
const char WALL  = '0' ;
const char GOAL  = 'G' ;

const int MapWidth = 10, MapHeight = 10;
//       Y pos      X pos
char Map[MapHeight][MapWidth] = {
    { '1', '1', 'G', '1', '1', '1', '1', '1', '1', '1' },
    { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
    { '1', '1', '0', '1', '1', '1', '1', '1', '0', 'G' },
    { '1', '1', '0', '0', '1', '1', '1', '1', '0', '1' },
    { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
    { '1', '1', '1', '1', '1', '1', '1', '0', '0', '1' },
    { '1', '1', '1', '1', '1', '1', '1', '0', '1', '1' },
    { '1', '1', '1', '0', '0', '1', '1', '0', '1', '1' },
    { '1', '1', '0', '0', '0', '1', '1', '0', '0', '0' },
    { '1', '1', '1', 'G', '0', '1', '1', '1', '1', '1' }
};

struct Pos
{
    short x,y;
	Pos operator + ( Pos p ) const { return Pos(x+p.x,y+p.y); }
	bool operator < ( Pos p ) const { return ( y==p.y ) ? (x<p.x) : (y<p.y) ; }
	bool operator != ( Pos p ) const { return ( y!=p.y ) || (x!=p.x) ; }
    Pos(short x=0,short y=0) : x(x), y(y) {}
};

bool valid(Pos p) { return p.x>=0 && p.x<MapWidth && p.y>=0 && p.y<MapHeight; }

enum Dir { d_beg, d_up=d_beg, d_rg, d_dn, d_lf, d_end };

Pos deltas[d_end] = { {0,-1}, {+1,0}, {0,+1}, {-1,0} };

Dir& operator ++ ( Dir& d ) { d = (Dir) ( 1+(int)d ) ; return d; }

Dir other(Dir d)
{
	switch(d)
	{
	case d_up: return d_dn;
	case d_rg: return d_lf;
	case d_dn: return d_up;
	case d_lf: return d_rg;
	default: return d_end;
	}
}

struct SearchMapItem
{
	bool traversble;
	bool goal;
	bool visited;
	int cost_here;
	Dir came_from;
	bool paths[d_end];
};

map<Pos,SearchMapItem> search_map;
typedef map<Pos,SearchMapItem>::iterator SMII;

void MakeMap()
{
	search_map.clear();
	Pos p;
	for(p.y=0;p.y<MapHeight;++p.y) for(p.x=0;p.x<MapWidth;++p.x) 
	{
		SearchMapItem smi;
		smi.visited = false;
		smi.cost_here = -1;
		smi.came_from = d_end;
		if( Map[p.y][p.x] == WALL )
		{
			smi.traversble = false;
		}
		else if( Map[p.y][p.x] == GOAL )
		{
			smi.traversble = true;
			smi.goal = true;
		}
		else if( Map[p.y][p.x] == FLOOR )
		{
			smi.traversble = true;
			smi.goal = false;
			for( Dir d = d_beg; d != d_end; ++d )
			{
				Pos p2 = p + deltas[d];
				smi.paths[d] = valid(p2) && (Map[p2.y][p2.x] != WALL) ;
			}
		}
		search_map[p] = smi;
	}
}

void FindGoalFrom( Pos start )
{
	vector<SMII> found;

	{
		SMII smii = search_map.find(start);

		if(smii==search_map.end()) { cout << "starting outside map\n"; return; }
		if(smii->second.goal) { cout << "already at target\n"; return; }
		if(!smii->second.traversble) { cout << "starting in a wall\n"; return; }

		smii->second.visited = true;
		smii->second.cost_here = 0;
		found.push_back(smii);
	}

	int cost_so_far = 0;
	bool did_find = false;

	while(!did_find)
	{

		vector<SMII> candidates;

		for( SMII smii : found )
		{
			for( Dir d = d_beg; d != d_end; ++d )
			{
				if( ! smii->second.paths[d] ) continue;
				Pos p = smii->first + deltas[d];
				if(!valid(p)) continue;
				SMII cand = search_map.find(p);
				if(cand==search_map.end()) continue;
				if(cand->second.visited) continue;
				cand->second.came_from=d;
				candidates.push_back(cand);
			}
		}

		++cost_so_far;

		if( candidates.empty() ) break;

		for( SMII smii : candidates )
		{
			smii->second.visited = true;
			smii->second.cost_here = cost_so_far;
			found.push_back(smii);
			if( smii->second.goal ) { did_find = true; break; }
		}

	}

	if( ! did_find ) { cout << "no goal reachable\n"; return; }

	SMII pos = found.back();

	vector<Dir> path;

	while( pos->first != start )
	{
		Dir d = pos->second.came_from;
		path.push_back(d);
		Pos p = pos->first + deltas[ other(d) ];
		pos = search_map.find(p);
	}

	for( auto itr = path.rbegin(); itr != path.rend(); ++itr )
	{
		const char* dir_names[] = { "Up", "Right", "Down", "Left" } ;
		cout << "Walk " << dir_names[*itr] << endl;
	}
	cout << "Then you are at goal in total " << to_string(cost_so_far) << " steps" << endl;
}

int main()
{
    MakeMap();
    
    FindGoalFrom( Pos(5,9) );
    
    cout << "\ndone\n";
}
