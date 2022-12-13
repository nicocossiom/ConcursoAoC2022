// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <aocutils.h>
using namespace std;

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(10);
    string line;
    int x_register = 1; 
    int cycles = 0; 
    vector<int> signal_strengths(6);
    int current_cycle_sample = 20; 
    auto next_cycle = [&cycles, &current_cycle_sample, &x_register, &signal_strengths](){
        cycles++;
        if(cycles == current_cycle_sample) {
            cout << "Next cycle: " << current_cycle_sample << " -> " << x_register <<" * " <<current_cycle_sample << endl;
            signal_strengths.push_back(x_register * current_cycle_sample); 
            current_cycle_sample += 40;
        }
    };
    while (getline(input, line) && current_cycle_sample <= 220) {
        // separate by first space
        size_t pos = line.find(' ');
        string first = line.substr(0, pos);
        next_cycle();
        if(first == "addx") {
            next_cycle(); 
            x_register += stoi( line.substr(pos + 1) );
        }
    }
    // sum all the elements in the vector
    int sum = 0;
    for_each(signal_strengths.begin(), signal_strengths.end(), [&sum](int x){sum += x;});
    cout << "Suma de las señales: " << sum << endl;
}

void render(const vector<vector<char>>& crt) {
    for(auto row : crt) {
        for(auto col : row) {
            cout << col;
        }
        cout << endl;
    }
}

void parte2() {
    cout << "Parte 2" << endl;
    fstream input = get_input_stream(10);
    string line;
    int x_register = 1;
    int cycles = 0;
    vector<vector<char>> crt(6, vector<char>(40));
    auto gen_new_pixel = [&cycles, &x_register, &crt](){
        auto row = (int) trunc((cycles-1) / 40);
        int col = (cycles-1) % 40;
        // see if the x_register is within col +- 1
        crt[row][col] = (abs(x_register - col) <= 1) ? '#' : ' '; 
    };
    while (getline(input, line) && cycles < 240) {
        size_t pos = line.find(' ');
        string first = line.substr(0, pos);
        cout << "cycles: " << cycles << endl;
        cycles++; 
        gen_new_pixel();
        if(first == "addx") {
            cycles++; 
            gen_new_pixel();
            x_register += stoi( line.substr(pos + 1) );
        }
    }
    render(crt);
}
int main () {
    cout << "Dia 9" << endl;
    parte1();
    parte2();
    return 0;
}