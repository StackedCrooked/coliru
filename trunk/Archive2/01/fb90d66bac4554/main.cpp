#include <map>

//Very rough implementation of a specialized interval tree
//TODO: Replace std::map with a custom red-black tree implementation or something similar

typedef unsigned short ui16;

template <typename T>
class IntervalTree {
public:

    struct Node {
        Node(T Data, ui16 Length) : data(Data), length(Length) {}
        T data;
        ui16 length;
    };

    inline void clear() {
        std::map<ui16, Node>().swap(_tree);
    }

    inline typename std::map<ui16, Node>::iterator getInterval(ui16 index) {
        auto it = _tree.lower_bound(index);
        if (it->first != index) {
            return it--;
        }
        return it;
    }

    inline typename std::map<ui16, Node>::iterator insert(std::pair<ui16, Node> pair) {
        return _tree.insert(pair);
    }

     typename std::map<ui16, Node>::iterator insert(ui16 index, T data) {
        //Find containing interval
        auto it = _tree.lower_bound(index);
        if (it->first != index) {
            it--;
        }
        //Its already in the tree
        if (it->second.data == data) {
            return it;
        }

        //If the interval is only 1, just change its value
        if (it->second.length == 1) {
            it->second.data = data;
            return it;
        }

        //Check if its at the right edge of the interval
        if (index == it->first + it->second.length - 1) {

            auto next = it + 1;
            //if it should add to the next interval
            if (data == next->second.data) {
                it->second.length--;
                it = _tree.insert(make_pair(index, Node(data, next->second.length + 1)));
                _tree.erase(next);
                return it;
            } else { //else we should add an interval and modify left interval
                //Modify left interval
                it->second.length--;
                //Insert new interval
                return _tree.insert(make_pair(index, Node(data, 1)));
            }
        } else if (index == it->first) { //if its at the beginning of the interval
            //Insert right interval
            _tree.insert(make_pair(index + 1, Node(it->second.data, it->second.length - 1)));
            _tree.erase(it);
            _tree.insert(make_pair(index, Node(data, 1)));
        } else { //else its in the middle of the interval
            //Insert right interval
            _tree.insert(make_pair(index + 1, Node(it->second.data, it->second.length - (index - it->first) - 1)));
            //Modify left interval
            it->second.length = index - it->first;
            //Insert new middle interval
            return _tree.insert(make_pair(index, Node(data, 1)));
        }
        return _tree.end();
    }

    inline typename std::map<ui16, Node>::iterator begin() const { return _tree.begin(); }
    inline typename std::map<ui16, Node>::iterator end() const { return _tree.end(); }

private:
    std::map <ui16, Node> _tree;
};

int main()
{
    IntervalTree<int> it;
    auto _it = it.getInterval(0);
}