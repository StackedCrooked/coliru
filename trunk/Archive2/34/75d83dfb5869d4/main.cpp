// Done!
// Bryan Owens, Bronze level


#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

// streams:
ifstream fin ("auto.in");
ofstream fout ("auto.out");

// vars:
long num_words;
string words_list[1000000];
string sorted_words_list[1000000];
int num_partials;
string partials_list[1000];
long partials_indexes[1000];
long found_solution_indexes[1000];


int starts_with(int partials_list_index, long sorted_words_list_index, long pos) {      // 1 == yes, 0 == no 
    if (pos == partials_list[partials_list_index].length()) {
        return 1;
    }
    if (pos == sorted_words_list[sorted_words_list_index].length()) {
        return 0;
    }
    string temp = sorted_words_list[sorted_words_list_index];
    string temp2 = partials_list[partials_list_index];
    if (temp[pos] == temp2[pos]) {
        return starts_with(partials_list_index, sorted_words_list_index, pos + 1);
    }
    return 0;
}

int find_index_from_string(string x) { 
    for (int j = 0; j < num_words; j++) {
        if (words_list[j] == x) {
            return j;
        }
    }
    return 0;
}


void compare_all_for_one_partial(int partials_list_index, long num_solutions, long expected_solution_num) {   // expected_solution_num counts from 1, be careful
    for (long j = 0; j < num_words; j++) {
        if (starts_with(partials_list_index, j, 0) == 1) {
            num_solutions++;
            if (num_solutions == expected_solution_num) {
      //          cout << "Found what you're looking for: the solution #" << expected_solution_num << " is: " << find_index_from_string(sorted_words_list[j]) + 1 << endl;   // j + 1
       //         cout << find_index_from_string(sorted_words_list[j]) + 1 << ", which is " << sorted_words_list[j] << endl;
                fout << find_index_from_string(sorted_words_list[j]) + 1 << "\n";
                return;
            }
       //     cout << sorted_words_list[j] << endl;
        }
    }
    if (num_solutions < expected_solution_num) {
        fout << -1 << "\n";
    }
 //   cout << num_solutions << " solutions" << endl;
}



int main() {

    fin >> num_words >> num_partials;
    
    for (long i = 0; i < num_words; i++) {
        string temp;
        fin >> temp;
        words_list[i] = temp;
        sorted_words_list[i] = temp;
    }
    
    for (long i = 0; i < num_partials; i++) {
        fin >> partials_indexes[i] >> partials_list[i];
    }

   // sort(begin(sorted_words_list), begin(sorted_words_list) + num_words - 1);
   // sort(sorted_words_list.begin(), sorted_words_list.begin() + num_words - 1);
   sort(sorted_words_list, sorted_words_list + num_words - 1);
    
/*
    for (int j = 0; j < num_words; j++) {
        cout << sorted_words_list[j] << endl;
    }
*/  
    
 //   cout << "-----" << endl;
    
    for (int k = 0; k < num_partials; k++) {
         compare_all_for_one_partial(k, 0, partials_indexes[k]);
    }



}