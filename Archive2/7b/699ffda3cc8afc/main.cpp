#include <iostream>
#include <vector>
#include <map>
#include <string>

//Affichage
using std::cout;

//Conteneur
using std::vector;
using std::string;
using std::map;


//Interface commune aux différentes map
template<class Key>
class GenericMapWrapper {
 public:
  virtual bool getKey(Key& k) = 0;
  virtual void increment(Key const& k) = 0;
  virtual bool isEnd() = 0;
  virtual void reinit() = 0;
  virtual ~GenericMapWrapper() {}
};

//Gestion spécifique des itérateurs au sein de la map
template<class Key, class Value>
class MapWrapper : public GenericMapWrapper<Key> {
 public:
  MapWrapper(map<Key,Value> const& map) : _map(map) { reinit(); }
  ~MapWrapper() {}
  
  //Fonctions interface générique
  bool getKey(Key& k);
  void increment(Key const& k);
  bool isEnd() { return _it == _map.end(); }
  void reinit() { _it = _map.begin(); }

  //Fonction spécifique
  bool getValue(Key const& k, Value& v);
  
 private:
  map<Key, Value> _map;
  typename map<Key, Value>::iterator _it;
};

//Renvoie la clé sur laquelle est positionné l'itérateur, et indique si elle est valide
template<class Key, class Value>
bool MapWrapper<Key, Value>::getKey(Key& k) {
  if (isEnd())
    return false;
  k = _it->first;
  return true;
}

//Incrément l'itérateur uniquement si la clé courante est égale à celle passée en argument
template<class Key, class Value>
void MapWrapper<Key, Value>::increment(Key const& k) {
  Key localKey;
  if (getKey(localKey) && localKey == k) {
    ++_it;
  }
}
 
//Renvoie la valeur sur laquelle est positionné l'itérateur, et indique si cette valeur est valide (c-à-d correspond à la clé passée en argument)
template<class Key, class Value>
bool MapWrapper<Key, Value>::getValue(Key const& k, Value& v) {
  if (isEnd())
    return false;
  v = _it->second;
  return _it->first == k;
}

//Classe gérant un tableau de map dont les clés sont les mêmes
template<class Key>
class Array {
 public:
  ~Array();
  
  //Gestion des lignes
  template<class Value> void addMap(map<Key, Value> const& map);
  template<class Value> bool getValue(Value& v);
  void incrementRow(); 
  bool isEnd();
  void reinit();

 private:
  typedef typename vector<GenericMapWrapper<Key>*>::iterator ArrayIterator;
  void computeCurKey();

  vector<GenericMapWrapper<Key>*> _array;
  Key _curKey;
};

template<class Key>
Array<Key>::~Array() {
  ArrayIterator it = _array.begin();
  while (!_array.empty()) {
    delete *it;
    it = _array.erase(it);
  }
}

template<class Key>
template<class Value> void Array<Key>::addMap(map<Key, Value> const& map) {
  _array.push_back(new MapWrapper<Key, Value>(map));
  computeCurKey();
}

template<class Key>
template<class Value> bool Array<Key>::getValue(Value& v) {
 MapWrapper<Key, Value>* pMapWrapper;
 for (ArrayIterator it = _array.begin(); it != _array.end(); ++it) {
   pMapWrapper = dynamic_cast<MapWrapper<Key, Value>*>(*it);
   if (pMapWrapper != NULL) {
     return pMapWrapper->getValue(_curKey, v);
   }
 }
 return false;
}

template<class Key>
void Array<Key>::incrementRow() {
  for (ArrayIterator it = _array.begin(); it != _array.end(); ++it) {
    (*it)->increment(_curKey);
  }
  computeCurKey();
}

template<class Key>
bool Array<Key>::isEnd() {
  bool isEnd = true;
  for (ArrayIterator it = _array.begin(); it != _array.end(); ++it) {
    isEnd = isEnd && (*it)->isEnd();
  }
  return isEnd;
}

template<class Key>
void Array<Key>::reinit() {
  for (ArrayIterator it = _array.begin(); it != _array.end(); ++it) {
    (*it)->reinit();
  }
  computeCurKey();
}

template<class Key>
void Array<Key>::computeCurKey() {
  bool isFirstValue = true;
  Key localKey;
  for (ArrayIterator it = _array.begin(); it !=_array.end(); ++it) {
    if ((*it)->getKey(localKey)) {
      if (isFirstValue) {
        _curKey = localKey;
        isFirstValue = false;
      } else {
        _curKey = std::min (_curKey, localKey);
      }
    }
  }
}

int main() {
  typedef map<int, int> TM1; typedef map<int, string> TM2; typedef map<int, char> TM3;
  TM1 m1; TM2 m2; TM3 m3;
  
  m1[1] = 1; m1[2] = 2; m1[3] = 3;                         m1[5] = 5;                m1[7] = 7;
                        m2[3] = "trois"; m2[4] = "quatre"; m2[5] = "cinq";
                                                           m3[5] = '5'; m3[6] = '6'; m3[7] = '7';
  
  Array<int> A;
  A.addMap<int>(m1); A.addMap<string>(m2); A.addMap<char>(m3);
  int i; string s; char c;
  while (!A.isEnd()) {
    cout << "int: "; if (A.getValue<int>(i)) cout << i; else cout << "N/A"; cout<< " ";
    cout << "string: "; if (A.getValue<string>(s)) cout << s; else cout << "N/A"; cout<< " ";
    cout << "char: "; if (A.getValue<char>(c)) cout << c; else cout << "N/A"; cout<< "\n";
    A.incrementRow();
  }
  A.reinit();
  cout << "int: "; if (A.getValue<int>(i)) cout << i; else cout << "N/A"; cout<< " ";
  cout << "string: "; if (A.getValue<string>(s)) cout << s; else cout << "N/A"; cout<< " ";
  cout << "char: "; if (A.getValue<char>(c)) cout << c; else cout << "N/A"; cout<< "\n";
}