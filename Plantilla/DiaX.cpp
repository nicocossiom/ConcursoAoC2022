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

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(3, 1);
    string line;
    while (getline(input, line)) {
        int item_size = line.length()/2;
        string first = line.substr(0, item_size);
        string second = line.substr(item_size, item_size);

    }
}


int parte2() {
    cout << "Parte 2" << endl;
    string line; 
    fstream input = get_input_stream(e, 2);
    while (getline(input, line)) {
        
    }
}

int main () {
    cout << "Dia X" << endl;
    parte1();
    parte2();
    return 0;
}