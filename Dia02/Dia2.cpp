// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
// import priority_queue

#include <string>
#include <fstream>
#include <aocutils.h>

using namespace std;

int translate_char(char c) {
    if (c == 'A' || c == 'X') return 1;
    else if (c == 'B' || c == 'Y') return 2;
    else return 3; // C or Z
}

int parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(2, 1);
    string line;
    int score = 0;
    while(getline(input, line)) {
        int opponent = translate_char(line[0]);
        int me = translate_char(line[2]);
        int fight = me - opponent;
        if(fight == 0) score+=3; // same -> tie
        else if(fight == 1 || fight == -2) score += 6; // ROCK vs PAPER, PAPER VS SCISSORS, SCISSORS VS ROCK
        score += me;
    }
    cout << score << endl;
    return 0;
}

void parte2() {
    cout << "Parte 2" << endl;
    fstream input = get_input_stream(2, 2);
    string line;
    int score = 0;
    while(getline(input, line)) {
        int opponent = translate_char(line[0]); 
        char outcome = line[2];
        int i = 1; 
        // initialize res RPS to null
        while (i <= 3 ) {
            int fight = i - opponent;
            if(fight == 0 && outcome == 'Y'){
                score+=3; // same -> tie
                break;
            } 
            else if((fight == 1 || fight == -2) && outcome == 'Z') {
                score += 6; // ROCK vs PAPER, PAPER VS SCISSORS, SCISSORS VS ROCK
                break;
            }
            else if( (fight == -1 || fight == 2) && outcome == 'X') break;
            i++; 
        }
        score += i;
    }
    cout << score << endl;
}

int main() {
    cout << "Dia 2" << endl;
    parte1();
    parte2();
    return 0;
}