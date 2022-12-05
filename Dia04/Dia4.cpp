// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <aocutils.h>
#include <vector>
using namespace std;

vector<vector<int>> separate_into_pair_of_pairs(string &to_separate){
    size_t comma_index = to_separate.find(","); 
    vector<string> pairs_unp (2);
    pairs_unp[0] = to_separate.substr(0, comma_index);
    pairs_unp[1] = to_separate.substr(comma_index+1, to_separate.size());
    vector<vector<int>> pairs (2, vector<int>(2));
    for(int i = 0; i < 2; i++){
        int sep_pos = pairs_unp[i].find('-');
        pairs[i][0] = stoi(pairs_unp[i].substr(0, sep_pos));
        pairs[i][1] = stoi(pairs_unp[i].substr(sep_pos+1, pairs_unp[i].size()));
    }
    return pairs;
}

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(4, 1);
    string line;
    int number_overlappings = 0;
    while (getline(input, line)) {
        vector<vector<int>> pairs = separate_into_pair_of_pairs(line);
        // cout << endl;
        if (pairs[0][0] <= pairs[1][0] && pairs[0][1] >= pairs[1][1]
            || pairs[1][0] <= pairs[0][0] && pairs[1][1] >= pairs[0][1]) {
            number_overlappings++;
        }
    }
        cout << number_overlappings << endl;

}

void parte2() {
    cout << "Parte 2" << endl;
    string line; 
    fstream input = get_input_stream(4, 2);
    int number_overlappings = 0; 
    while (getline(input, line)) {
        vector<vector<int>> pairs = separate_into_pair_of_pairs(line);
        if (pairs[0][1] >= pairs[1][0] && pairs[1][1] >= pairs[0][0]) {  
            // print the pairs
            cout << pairs[0][0] << "-" << pairs[0][1] << " " << pairs[1][0] << "-" << pairs[1][1] << endl;
            number_overlappings++;
        }
    }
    cout << number_overlappings << endl;
}

int main () {
    cout << "Dia X" << endl;
    parte1();
    parte2();
    return 0;
}