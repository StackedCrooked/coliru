//http://coliru.stacked-crooked.com/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <random>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm_ext/insert.hpp>
/*#include <boost/range/algorithm/transform.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/generate.hpp>
#include <boost/range/algorithm_ext/insert.hpp>
#include <boost/range/algorithm/min_element.hpp> 
#include <boost/range/adaptor/filtered.hpp>*/
using namespace std;
using namespace boost;
typedef string CodeMapDimension;
typedef vector<CodeMapDimension> CodeMap;
CodeMap testMap_ = {
    "        ",
    " X X    ",
    " X XX XX",
    "XX X    ",
    "   X X  ",
    "  XX    ",
    " X      ",
    "   X    "};

typedef vector<char> MapDimension;
typedef vector<int> FieldDimension;
typedef vector<MapDimension> Map;
typedef vector<FieldDimension> Field;
struct Point{
    int x, y;
    friend bool operator==(const Point& l, const Point& r){
        return l.x==r.x && l.y==r.y;
    }
    friend Point operator+(const Point& l, const Point& r){
        return {l.x+r.x, l.y+r.y};
    }
    friend ostream& operator<<(ostream& stream, const Point& point){
        stream<<"("<<point.x<<", "<<point.y<<")";
        return stream;
    }
    Point& operator=(const Point& p) = default;
};
typedef list<Point> Path;

const char wall  = 'X';
const char void_ = ' ';
const char step  = '*'; 

//UB на не квадратных картах.
Map toMap(const CodeMap& map){
    Map r(map.size());
    transform(map, r.begin(),
        [](const CodeMapDimension& line){
            MapDimension r(line.size());
            copy(line, r.begin());
            return r;
        });
    return r;
    /* 
            *vs* 
    Map ro(map.size());
    size_t i=0;//Можно чисто через итераторы, но длинее и я так всегда делаю, поэтому не интересно. 
    for(const CodeMapDimension& line: map)
    {
        MapDimension& r(ro[i++]);
        r.resize(line.size());
        size_t j=0;
        for(const char topographic: line)
            r[j++]=topographic;
    }
    return ro;*/            
}

Map generateMap(const int w, const int h, const double wallFactor, const int seed){
    default_random_engine engine_generator(seed);
    uniform_int_distribution<> distribution(0,1000);
    auto rand = bind(distribution, engine_generator);
    const auto generator = [&rand, wallFactor](){if(rand()/1000.0<wallFactor) return wall; else return void_;};
    Map r(h);
    return generate(r, [w, generator](){
        MapDimension r(w);
        return generate(r, generator);
    });
}

void outputMap(const Map& map){
    cout<<endl;
	if(map.empty())
	{
		cout<<"o_O"<<endl;
		return;
	}	
    ostream_iterator<char> out(cout);
    ::std::fill_n(out, map[0].size()+2, '_');
    cout<<endl;
    for(const MapDimension& line: map){
        cout<<"|";
        copy(line, out);
        cout<<"|"<<endl;
    };
    ::std::fill_n(out, map[0].size()+2, '-');
    cout<<endl;
}

Point mapSize(const Map& map)
{
	if(map.empty())
		return {0, 0};
	return {(int)map[0].size(), (int)map.size()};
}

template<class T>
typename T::value_type::value_type& atPoint(T& twoDimensionContainer, const Point& point){
    return twoDimensionContainer[point.y][point.x];
}

template<class T>
const typename T::value_type::value_type& atPoint(const T& twoDimensionContainer, const Point& point){
    return twoDimensionContainer[point.y][point.x];
}

Map fillPathOnMap(const Map& map, const Path& path){
    Map r(map.size());
    copy(map, r.begin());
    for(const Point& point: path)
        atPoint(r, point)=step;
    return r;
}

bool inMapRange(const Map& map, const Point& point){
    if(map.empty())
        return false;
    return point.x>=0 && point.y>=0 && point.x<(int)map[0].size() && point.y<(int)map.size();
}

bool isPassably(const Map& map, const Point& point){
    return inMapRange(map, point) && atPoint(map, point)!=wall;
}

void outputPath(const Path& path){
    copy(path, ostream_iterator<Point>(cout));
}

Field fieldConstruct(const Map& map){
    const size_t
            w = map[0].size(),
            h = map.size(),
            maxField = w*h+1;
    return Field(h, FieldDimension(w, maxField));
}

bool stepIsNotFolly(const Map& map, const Field& field, const int waveDistance, const Point& point){
    return isPassably(map, point) && waveDistance<atPoint(field, point);
}

Path nearPoints(const Point& point)
{
    Path path = {point + Point({-1,0}), point + Point({1,0}), point + Point({0,-1}), point + Point({0,1})};
    return path;
}

Path nextPoints(const Map& map, const Field& field, const int waveDistance, const Point& point)
{
    auto path = nearPoints(point);
    auto r = adaptors::filter(path, bind(stepIsNotFolly, map, field, waveDistance, placeholders::_1)); 
    return Path(r.begin(), r.end());
}

Path nextPointsForPathTraversing(const Map& map, const Point& point)
{
    auto path = nearPoints(point);
    auto r = adaptors::filter(path, bind(inMapRange, map, placeholders::_1)); 
    return Path(r.begin(), r.end());
}

Path fillPath(const Map& map, const Field& field, const Point& source, const Point& destination)
{
	auto currentPoint = source;
	Path path = {source};
	while(!(currentPoint==destination))
    {   
        const auto nextPoints = nextPointsForPathTraversing(map, currentPoint);
		path.push_back(currentPoint = *min_element(nextPoints, 
			[&field](const Point& l, const Point& r){
				return atPoint(field, l)<atPoint(field, r);
			}));
    }
	return path;
}

Path pathFind(const Map& map, const Point& source, const Point& destination){
	if(map.empty())
		return Path();
    if(!((inMapRange(map, source))&&(inMapRange(map, destination))))
        return Path();
    if(!isPassably(map, destination))
        return Path();
    Path waveFront = {destination};
	auto field = fieldConstruct(map);
	int waveDistance = 0;
	const auto waveFrontEnd = waveFront.cend();
	auto currentPoint = waveFront.begin();
	while(currentPoint!=waveFrontEnd)
	{
		while(currentPoint!=waveFrontEnd)
		{
			atPoint(field, *currentPoint)=waveDistance;
			if(source==*currentPoint)
				return fillPath(map, field, source, destination);
			insert(waveFront, currentPoint, nextPoints(map, field, waveDistance, *currentPoint));
			waveFront.erase(currentPoint++);
		}
		currentPoint = waveFront.begin();
		++waveDistance;
	}
	return Path();
}

void viewPath(const Map& map, const string& mapName, const Point& source, const Point& destination)
{
	cout<<"Map "<<mapName<<" with size "<<mapSize(map)<<":";
	outputMap(map);
	cout<<"Path from "<<source<<" to "<<destination<<":"<<endl;
	auto path = pathFind(map, source, destination);
    outputPath(path);
	cout<<endl<<"Map with path: ";
	auto mapWithPath = fillPathOnMap(map, path);
	outputMap(mapWithPath);
	cout<<endl<<endl<<endl;
}

int main()
{
    const auto testMap = toMap(testMap_);
    viewPath(testMap, "Code map", {0,0}, {5,5});
    const auto map1 = generateMap(10,16, 0.2, 0);
    viewPath(map1, "Generated map1", {2,2},{8,8});
	const auto map2 = generateMap(16,10, 0.3, 50);
    viewPath(map2, "Generated map2", {2,2},{14,8});
}
