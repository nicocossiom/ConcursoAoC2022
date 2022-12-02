// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
// import priority_queue

#include <string>
#include <fstream>
#include <aocutils.h>

using namespace std;

using RPS = enum class RPS{ ROCK = 1, PAPER = 2, SCISSORS = 3};
using RPSRound =  struct { RPS opponent; RPS me; };
template <typename E>
constexpr typename std::underlying_type<E>::type to_underlying(E e) noexcept {
    return static_cast<typename std::underlying_type<E>::type>(e);
}

RPS translate_char(char c) {
    if (c == 'A' || c == 'X') return RPS::ROCK;
    else if (c == 'B' || c == 'Y') return RPS::PAPER;
    else return RPS::SCISSORS; // C or Z
}
RPSRound translate_input(string input_string){
    RPSRound round = {translate_char(input_string[0]), translate_char(input_string[2])};
    return round;
}

int main() {
    fstream input = get_input_stream(2, ChallengePart::A);
    string line;
    int score = 0;
    while(getline(input, line)) {
        RPSRound round = transalate_input(line);
        int fight = to_underlying(round.me) - to_underlying(round.opponent);
        if(fight == 0) score+=3; // same -> tie
        else if(fight == 1 || fight == -2) score += 6; // ROCK vs PAPER, PAPER VS SCISSORS, SCISSORS VS ROCK
        score += to_underlying(round.me);
    }
    cout << score << endl;
    return 0;
}