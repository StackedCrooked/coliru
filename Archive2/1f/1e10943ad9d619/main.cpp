#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

class Permutation {
public:
    /* element of the orbit*/
    struct ei_element {
        int e; /* identity index */
        int i; /* actual permutation index */
    };
    typedef std::vector<ei_element> Orbit; /* a cycle */

    Permutation( std::vector<int> const& i_vector);
    /* permute i element, vector is 0 indexed */
    int pi( int i) const { return iv[ i - 1]; }
    /* i_k = pi(k) */
    int i( int k) const { return pi( k); }
    int q() const { /* TODO: return rank = q such that pi^q = e */ return 0; }
    int n() const { return n_; }
    /* return the sequence 1, 2, ..., n */
    std::vector<int> const& Omega() const { return ev; }
    /* return vector of cycles */
    std::vector<Orbit> const& orbits() const { return orbits_; }
    /* return length of k-th cycle */
    int l( int k) const { return orbits_[ k].size(); }
    /* return sum of all transpositions */
    int transpositionsCount() const;
    void make_orbits();
    
private:
    struct Increment {
        int current;
        Increment(int start) : current(start) {
        }
        int operator() () {
            return current++;
        }
    };
    int n_;
    std::vector<int> iv; /* actual permutation */
    std::vector<int> ev; /* identity permutation */
    std::vector<Orbit> orbits_;
};

Permutation::Permutation( std::vector<int> const& i_vector) : n_( i_vector.size()), 
                                                     iv( i_vector), ev( n_)
    {
        if ( n_) {
            /* fill identity vector 1, 2, ..., n */
            Increment g ( 1);
            std::generate( ev.begin(), ev.end(), g);
        }
    }

/* create orbits (cycles) */
void Permutation::make_orbits() {
    std::set<int> to_visit( ev.begin(), ev.end()); // identity elements to visit
    
    while ( !to_visit.empty()) {
        /* new cycle */
        Orbit orbit;
        int first_to_visit_e = *to_visit.begin();
        to_visit.erase( first_to_visit_e);
        int k = first_to_visit_e; // element in identity vector
        /* first orbit element */
        ei_element element;
        element.e = first_to_visit_e;
        element.i = i( first_to_visit_e);
        orbit.push_back( element);
        
        /* traverse permutation until cycle is closed */
        while ( pi( k) != first_to_visit_e && !to_visit.empty()) {
            k = pi( k);
            ei_element element;
            element.e = k;
            element.i = pi( k);
            orbit.push_back( element);
            to_visit.erase( k);
        }
        orbits_.push_back( orbit);
    }
}
/* return sum of all transpositions */
int Permutation::transpositionsCount() const {
    int count = 0;
    int k = 0;
    while ( k < orbits_.size()) {
        count += l( k++) - 1; /* sum += l_k - 1 */ 
    }
    return count;
}
/*
 * 
 */
int main(int argc, char** argv) {
                       //1, 2, 3, 4, 5, 6, 7, 8       identity (e)
    int permutation[] = {2, 3, 4, 5, 1, 7, 6, 8}; //  actual (i)
    std::vector<int> vp(permutation, permutation + 8);

    Permutation p(vp);
    p.make_orbits();
    int k = p.orbits().size();
    std::cout << "Number of cycles:" << k << std::endl;
    
    for (int i = 0; i < k; ++i) {
        std::vector<Permutation::ei_element> v = p.orbits()[i];
        for (int j = 0; j < v.size(); ++j) {
            std::cout << v[ j].e << "," << v[ j].i << " | ";
        }
        std::cout << std::endl;
    }
    
    std::cout << "Steps needed to create identity permutation: " << p.transpositionsCount();
    return 0;
}

