# include <vector>
# include <algorithm>
# include <iostream>

// compile with                                                                                //
// /usr/lib/gcc-snapshot/bin/g++ -std=c++11 -o tiedrank tiedrank.cpp                           //
 
using namespace std;
 
int main() {

  // initialise unsorted data                                                                  //
  vector<double> 
    orig ( {6, 4, 4, 2, 2, 3, 3, 3, 3} );       // unsorted data                               //
  vector<size_t> 
    idxs (orig.size()        );                 // indices for sorting                         //
  
  iota(idxs.begin(), idxs.end(), 0);            // initialise indices                          //
  
  // show unsorted data
  cout << "unsorted data \nindex(i), vector(v), sort index(I), rank(R)\n\ni --> v[i] \n========== \n";
  for ( size_t i = 0; i < orig.size(); i++ ) 
    cout << i << " --> " << orig[i] << " " << idxs[i] << endl;
  
  // tie adjustments:                                                                          //
  // 0) minimum: ranks of a group of ties are the lowest rank in the group                     //
  // 1) average: ranks of a group of ties are the group average rank                           //
  // 2) maximum: ranks of a group of ties are the lowest rank in the group                     //
  for (unsigned rmod=0; rmod<3; rmod++) {

    // sort using standard algorithm                                                           //    
    cout << "\nsorting indices ... ";
    sort (idxs.begin(), idxs.end(), [&](size_t a, size_t b){
    return orig[a] < orig[b];       // sort idxs based on data in orig                     //
      } );
 
    // compute ranks, using minumum / average / maximum rank for ties                          //
    vector<double> 
      rnks ( orig.size()       );       // vector for data ranks                               //

    cout << "ranking with mode " << rmod << " ...\n\n";
    rnks[idxs[0]]=0;
    for (size_t i=1, radj=0, ties=0; i<orig.size(); i++) { 
      if (i && (orig[idxs[i-1]]!=orig[idxs[i]])) {
	if (ties)                       // non-tie after ties -> adjust previous ranks         //
	  switch(rmod) {
	  case 1: {                     // average: add #ties/2 to previous #ties ranks        //
	    for (size_t j=0; j<=ties; j++)
	      rnks[idxs[i-1-j]]+=double(ties)/2;
	    break; }
	  case 2: {
	    for (size_t j=0; j<=ties; j++)
	      rnks[idxs[i-1-j]]+=ties;  // maximum: add #ties to previous #ties ranks          //
	    break; }
	  }
	ties=0;                         // non-tie: set ties counter to 0                      //
      } else {
	ties++;                         // tie: increase ties counter                          //
      } 
      rnks[idxs[i]]=i-ties;             // ties are subtracted from ranks, stoppnig increments //
    }

    // show sorted indices and tie-adjusted ranks                                              //
    cout << "i --> v I R \n============= \n";
    for (size_t i=0; i<orig.size(); i++) 
      cout << i << " --> " << orig[i] << " " << idxs[i] << " " << rnks[i] << endl;
    cout << "i --> v I R\n";

  } // for rmod                                                                                //

}
