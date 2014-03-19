// codeSample.cpp: main program module. Simple code sample. 
//Find path on 2D map by simple breadth-first search algorithm.
//Not subdivided into several files.
//Not satisfy for release compilation.
//I like use BOOST-\STL- algorithms and write pure code with const-correctness and small self-documented functions,
// but can change my code style if required by Code Style Guidelines.

//http://coliru.stacked-crooked.com/

//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <random>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm_ext/insert.hpp>
#include <boost/range/numeric.hpp>
#include <assert.h>
#include <limits>
using namespace std;
using namespace boost;

class Point2D{
public:
  Point2D() = default;
  Point2D(const size_t x, const size_t y) :
    x(x),
    y(y)
  {}
  Point2D& operator=(const Point2D&) = default;
  Point2D(const Point2D&) = default;
  size_t X() const { return x; }
  size_t Y() const { return y; }
  friend bool operator==(const Point2D& l, const Point2D& r){
    return l.x == r.x && l.y == r.y;
  }
  Point2D add(const Point2D& r) const{
    return{ x + r.x, y + r.y };
  }
  Point2D subtract(const Point2D& r) const{
    return{ x + r.x, y + r.y };
  }
  friend ostream& operator<<(ostream& stream, const Point2D& point){
    //to do: Should use ::std::basic_ostream at industry code instead ::std::ostream.
    stream << "(" << point.x << ", " << point.y << ")";
    return stream;
  }

private:
  size_t x, y;
};

typedef string HardCodedMapDimension;
typedef vector<HardCodedMapDimension> HardCodedMap;
const HardCodedMap testMap = {
  "        ",
  " X X    ",
  " X XX XX",
  "XX X    ",
  "   X X  ",
  "  XX    ",
  " X      ",
  "   X    "
};

typedef vector<Point2D> Path;

enum class Mapel {
  wall = 'X',
  void_ = ' ',
  step = '*'
};

namespace{
  template<class Container2D>
  bool checkRectangularity(const Container2D& forVerify){
    if (forVerify.empty())
      return true;
    const auto width = forVerify[0].size();
    typedef typename Container2D::value_type Container;
    //to do: Should use template trait at industry code instead Container2D::value_type.
    return ::boost::accumulate(forVerify, true, [width](const bool forAll, const Container& forCheck){
      return forAll && (forCheck.size() == width);
    });
  }
}

template<class Item>
class Matrix{
public:
  typedef vector<Item> Dimension;
  typedef vector<Dimension> Repository;
  Matrix() = default;
  Matrix(const Matrix&) = default;
  //Matrix(Matrix&&) = default;
  Matrix(Matrix&& source)://workaround to above code for ms vs
    data(move(source.data))
  {}
  /*Matrix& operator=(const Matrix&) = default;
  Matrix& operator=(Matrix&&) = default;*/
  Matrix& operator=(Matrix source){//workaround to above code for ms vs
    this->data = move(source.data);
    return *this;
  }
  Matrix(Repository data) :
    data(move(data))
  {
    assert(checkRectangularity(this->data));
  }
  Item& operator[](const Point2D& point){
    return this->data[point.Y()][point.X()];
  }
  const Item& operator[](const Point2D& point) const {
    return this->data[point.Y()][point.X()];
  }
  bool inRange(const Point2D& point) const {
    if (this->data.empty())
      return false;
    return point.X()<this->width() && point.Y()<this->height();
  }
  size_t width() const{
    if (this->data.empty())
      return 0;
    return this->data[0].size();
  }
  size_t height() const{
    return this->data.size();
  }
  const Repository& constData() const{
    return this->data;
  }
private:
  Repository data;
};

class Map : public Matrix<Mapel>{
  typedef Matrix<Mapel> Base;
public:
  /*Map() = default;
  Map& operator=(const Map&) = default;
  Map& operator=(Map&&) = default;
  Map(const Map&) = default;
  Map(Map&&) = default;*/
  using Base::Matrix;//<Mapel>;
  using Base::operator=;
  /*Map(Repository map) :
    Base(move(map))
  {}*/
  explicit Map(const HardCodedMap& map) :
    Base(toMapRepository(map))
  {}
  static Map generateMap(const size_t width, const size_t height, const double wallFactor, const int seed){//Not labyrinth-friendly generator.
    assert(width<(numeric_limits<decltype(width)>::max)());
    assert(height<(numeric_limits<decltype(height)>::max)());
    assert((!width) || height);
    const int generatorGranularity = 1000;
    default_random_engine engine_generator(seed);
    uniform_int_distribution<> distribution(0, generatorGranularity);
    auto rand = bind(distribution, engine_generator);
    const auto generator = [&rand, wallFactor, generatorGranularity](){
      if (rand() / (1.*generatorGranularity)<wallFactor)
        return Mapel::wall;
      else
        return Mapel::void_;
    };
    Repository result(height);
    generate(result, [width, generator](){
      Dimension result(width);
      generate(result, generator);
      return result;
    });
    return result;
  }

  void fillPathOnMap(const Path& path){
    for (const Point2D& point : path)
      (*this)[point] = Mapel::step;
  }

  bool isPassable(const Point2D& point) const {
    return inRange(point) && (*this)[point] != Mapel::wall;
  }

  Path pathFind(const Point2D& source, const Point2D& destination) const{
    //Return empty Path-container, if path not found or call with invalid argument.
    if (!(isPassable(destination) && isPassable(source)))
      return Path();
    Wavefront wavefront = { destination };
    auto field = fieldConstruct();
    int waveDistance = 0;
    const auto wavefrontEnd = wavefront.end();
    auto currentPoint = wavefront.begin();
    while (!wavefront.empty())
    {
      while (currentPoint != wavefrontEnd)
      {
        field[*currentPoint] = waveDistance;
        if (source == *currentPoint)
          return fillPath(field, source, destination);
        insert(wavefront, currentPoint, nextPoints(field, waveDistance, *currentPoint));
        wavefront.erase(currentPoint++);
      }
      currentPoint = wavefront.begin();
      ++waveDistance;
    }
    return Path();
  }

  static Mapel charToMapItem(const char item){
    assert(item == char(Mapel::step) || item == char(Mapel::void_) || item == char(Mapel::wall));
    return static_cast<Mapel>(item);
  }

  static char mapItemToChar(const Mapel item){
    return static_cast<char>(item);
  }

private:
  static Repository toMapRepository(const HardCodedMap& map){
    assert(checkRectangularity(map));
    assert(map.size()<(numeric_limits<Repository::size_type>::max)());
    assert(map.empty() || map[0].size()<(numeric_limits<Dimension::size_type>::max)());
    assert(map.empty() || (!map[0].empty()));
    Repository result(map.size());
    transform(map, result.begin(),
      [](const HardCodedMapDimension& line){
      Dimension result;
      result.reserve(line.size());
      transform(line, back_inserter(result), charToMapItem);
      return result;
    });
    return result;
  }

  typedef Matrix<int> Field;
  typedef list<Point2D> Wavefront;
  typedef vector<Point2D> Points;

  Field fieldConstruct() const{
    const auto maxField = width()*height() + 1;
    return Field::Repository(height(), Field::Dimension(width(), maxField));
  }

  bool stepIsNotFolly(const Field& field, const int waveDistance, const Point2D& point) const {
    return isPassable(point) && waveDistance<field[point];
  }

  static Points nearPoints(const Point2D& point){
    return{ point.subtract({ 1, 0 }), point.add({ 1, 0 }), point.subtract({ 0, 1 }), point.add({ 0, 1 }) };
  }

  Points nextPoints(const Field& field, const int waveDistance, const Point2D& point) const {
    const auto path = nearPoints(point);
    const auto result = adaptors::filter(path, bind(&Map::stepIsNotFolly, this, field, waveDistance, placeholders::_1));
    return Points(result.begin(), result.end());
  }

  Points nextPointsForPathTraversing(const Point2D& point) const{
    const auto path = nearPoints(point);
    const auto result = adaptors::filter(path, bind(&Map::inRange, this, placeholders::_1));
    return Points(result.begin(), result.end());
  }

  Path fillPath(const Field& field, const Point2D& source, const Point2D& destination) const {
    auto currentPoint = source;
    Path path = { source };
    while (!(currentPoint == destination)){
      const auto nextPoints = nextPointsForPathTraversing(currentPoint);
      assert(!nextPoints.empty());
      if (nextPoints.empty())
        return Path();
      path.push_back(currentPoint = *min_element(nextPoints, [&field](const Point2D& current, const Point2D& next){
        return field[current]<field[next];
      }));
    }
    return path;
  }
};

namespace{
  void outputMap(ostream& stream, const Map& map){
    //to do: Should use ::std::basic_ostream at industry code instead ::std::ostream.
    stream << endl;
    if (map.constData().empty()){
      stream << "Empty map." << endl;
      return;
    }
    const size_t frameSize = 2;
    ostream_iterator<char> out(stream);
    ::std::fill_n(out, map.width() + frameSize, '_');
    stream << endl;
    for (const Map::Dimension& line : map.constData()){
      stream << "|";
      transform(line, out, &Map::mapItemToChar);
      stream << "|" << endl;
    };
    ::std::fill_n(out, map.width() + frameSize, '-');
    stream << endl;
  }

  template< class CharT, class Traits>
  void outputPath(basic_ostream<CharT, Traits>& stream, const Path& path){
    copy(path, ostream_iterator<Point2D>(stream));
  }

  void monolog(Map& map, const string& mapName, const Point2D& source, const Point2D& destination)
  {
    cout << "Map " << mapName << " with size " << Point2D(map.width(), map.height()) << ":";
    outputMap(cout, map);
    cout << "Path from " << source << " to " << destination << ":" << endl;
    const auto path = map.pathFind(source, destination);
    outputPath(cout, path);
    cout << endl << "Map with path: ";
    map.fillPathOnMap(path);
    outputMap(cout, map);
    cout << endl << endl << endl;
  }
}

int main(int argc, char* argv[])
{
  (void)argc; (void)argv;
  Map map0(testMap);
  monolog(map0, "Hard coded map", { 0, 0 }, { 5, 5 });
  auto map1 = Map::generateMap(10, 16, 0.2, 0);
  monolog(map1, "Generated map1", { 2, 2 }, { 8, 8 });
  auto map2 = Map::generateMap(16, 10, 0.3, 50);
  monolog(map2, "Generated map2", { 2, 2 }, { 14, 8 });
  return 0;
}