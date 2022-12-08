// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <aocutils.h>
#include <stack>
#include <vector>
#include <regex>
#include <optional>

using namespace std;

void stacks_printer(vector<deque<char>> stacks){
    // print the stacks without modifying them
    int i = 1; 
    for (auto stack: stacks){
        cout << "Stack " << i << ": ";
        for (auto c: stack){
            cout << c << " ";
        }
        i++; 
        cout << endl;
    }
}

void read_input(fstream& input, vector<deque<char>> &piles, vector<vector<int>> &instructions){
    string line; 
    while (getline(input, line)) {
        for (int i = 0; i < line.size(); i++) {
            char c = line[i];
            if (isdigit(c)){
                getline(input, line); // skip empty
                while (getline(input, line)) {
                    regex re("\\d+");
                    vector<string> matches;
                    for (sregex_iterator it(line.begin(), line.end(), re), end; it != end; ++it) {
                        matches.push_back(it->str());
                    }
                    instructions.push_back(vector<int>{stoi(matches[0]), stoi(matches[1]), stoi(matches[2])});
                }
                break; 
            }
            else if (isupper(c)){
                // crates
                int pile = (i-1)/4; 
                while (piles.size() < pile+1) {
                    piles.emplace_back();
                }
                piles[pile].push_front(c);
                
            }   
        }
    }
}

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(5);
    // read lines from input into string vector
    vector<vector<int>> instructions;
    vector<deque<char>> piles; 
    read_input(input, piles, instructions);
    // execute instructions
    for (const auto& instruction : instructions){
        int amount = instruction[0];
        int from = instruction[1]-1;
        int to = instruction[2]-1;
        cout << endl << "Move " << amount << " from " << from+1 << " to " << to+1 << endl;
        stacks_printer(piles);
        for (int i = 0; i < amount; i++) {
            piles[to].push_back(piles[from].back());
            piles[from].erase(piles[from].end()-1);
        }
        cout << "Result: " << endl;
        stacks_printer(piles);
    }
    // get the front of each stack
    string result = "";
    for (auto stack: piles){
        result += stack.back();
    }
    cout << "Result: " << result << endl;
}        

void parte2() {
    cout << endl << "Parte 2" << endl;
    fstream input = get_input_stream(5);
    // read lines from input into string vector
    vector<vector<int>> instructions;
    vector<deque<char>> piles; 
    read_input(input, piles, instructions);
    // execute instructions
    for (const auto& instruction : instructions){
        int amount = instruction[0];
        int from = instruction[1]-1;
        int to = instruction[2]-1;
        cout << endl << "Move " << amount << " from " << from+1 << " to " << to+1 << endl;
        stacks_printer(piles);
        // get the elements to move
        deque<char> to_move; 
        for (int i = 0; i < amount; i++) {
            to_move.push_front(piles[from].back());
            piles[from].erase(piles[from].end()-1);
        }
        // print the to_move
        cout << "To move: ";
        for (auto c: to_move){
            cout << c << " ";
        }
        cout << endl; 
        // insert the to_move in the to stack
        piles[to].insert(piles[to].end(), to_move.begin(), to_move.end());
        stacks_printer(piles);
    }
    // get the front of each stack
    string result = "";
    for (auto stack: piles){
        result += stack.back();
    }
    cout << "Result: " << result << endl;
}

int main () {
    cout << "Dia 5" << endl;
    // parte1();
    parte2();
    return 0;
}