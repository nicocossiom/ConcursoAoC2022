// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <aocutils.h>

using namespace std;

bool valid (string& to_check){
    // see if any characters in the string are repeated
    set<char> unique_chars;
    for (char c : to_check){
        if (unique_chars.find(c) != unique_chars.end()){
            return false;
        }
        unique_chars.insert(c);
    }
    return true;
}

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(6);
    string line;
    getline(input, line);
    int number_until_valid = 14; 
    string before_marker = line.substr(0, number_until_valid);
    int current_marker = number_until_valid;
    while(!valid(before_marker)){
        // delete the first character and add the next one
        before_marker = before_marker.substr(1, 13) + line[current_marker];
        current_marker++;
    }
    cout << "The answer is: " << current_marker << " Non-repeating: " << before_marker << endl;
}


void parte2() {
    cout << "Parte 2" << endl;
    string line; 
    fstream input = get_input_stream(6);
    while (getline(input, line)) {
        continue;
    }
}

int main () {
    cout << "Dia X" << endl;
    parte1();
    parte2();
    return 0;
}