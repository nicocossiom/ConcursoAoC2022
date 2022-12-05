// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>
#include <aocutils.h>

using namespace std;

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(3, 1);
    string line;
    int total = 0; 
    while (getline(input, line)) {
        auto item_size = int(floor(line.length()/2));
        string first = line.substr(0, item_size);
        string second = line.substr(item_size, item_size);
        set<char> first_set(first.begin(), first.end());
        set<char> second_set(second.begin(), second.end());
        set<char> intersection;
        set_intersection(first_set.begin(), first_set.end(), second_set.begin(), second_set.end(), inserter(intersection, intersection.begin()));
        char c = *intersection.begin(); 
        int val =  (c >= 'a' && c <= 'z') ? c - 96 :  c - 38; // not random number just ascii val setback
        total += val;
    }
        cout << total << endl;
}

void parte2() {
    cout << "Parte 2" << endl;
    fstream input = get_input_stream(3, 2);
    string line;
    vector<string> lines;
    int total = 0; 
    while (getline(input, line)) {
        lines.push_back(line);
    }
    while(!lines.empty()) {
        set<char> intersection;
        // get 3 lines from front of vector convert into sets and intersect them 
        for (int i = 0; i < 3; i++) {
            string line = lines.front();
            lines.erase(lines.begin());
            set<char> line_set(line.begin(), line.end());
            if (i == 0) {
                intersection = line_set;
            } else {
                set<char> new_intersection;
                set_intersection(intersection.begin(), intersection.end(), line_set.begin(), line_set.end(), inserter(new_intersection, new_intersection.begin()));
                intersection = new_intersection;
            }
        }
        char c = *intersection.begin();
        int val =  (c >= 'a' && c <= 'z') ? c - 96 :  c - 38; // not random number just ascii val setback
        total += val;
    }
    cout << total << endl;

}

int main () {
    cout << "Dia 3" << endl;
    parte1();
    parte2();
    return 0;
}