// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <aocutils.h>
#include <cmath>
#include <numeric>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <map>

using namespace std;
const map<string, function<u_int64_t(u_int64_t, u_int64_t)>> available_operations = {
    {"+", plus<u_int64_t>()}, 
    {"*", multiplies<u_int64_t>()}
}; 

class Monkey{
    public:
        int divisor;
        int number; 
        string operation;
        string second_operand; 
        map<bool, int> index_monkeys_available;
        deque<long int> items_held; 
        u_int64_t inspections = 0; 
        int worry_divisor;

        Monkey(vector<string> lines, const int& worry_divisor): worry_divisor(worry_divisor){
            this->number = stoi(lines[0].substr(lines[0].find(' ')+1));
            regex re("\\d+");
            for (sregex_iterator it(lines[1].begin(), lines[1].end(), re), end; it != end; ++it) {
                this->items_held.push_back(stoi(it->str()));
            }
            regex re2("([a-z]+) (\\*|\\+) ([a-z]+|\\d+)");
            for (sregex_iterator it(lines[2].begin(), lines[2].end(), re2), end; it != end; ++it) {
                this->operation = it->str(2);
                this->second_operand = it->str(3);
            }
            regex re3("\\d+");
            smatch match; 
            regex_search(lines[3], match, re3);
            this->divisor = (stoi(match[0]));
            regex_search(lines[4], match, re3);
            this->index_monkeys_available[true] = stoi(match[0]);
            regex_search(lines[5], match, re3);
            this->index_monkeys_available[false] = stoi(match[0]);

        }

        string items_to_string(){
            return fmt::format("Monkey {}: {}", this->number, fmt::join(this->items_held, ", "));
        }
};

class MonkeyGame{
    public:
        int common_denominator;
        vector<Monkey> monkeys = vector<Monkey>();

        explicit MonkeyGame(fstream &input, int worry_divisor){
            string line;           
            while (!input.eof()) {
                vector<string> lines;
                while(getline(input, line) && line != "") {
                    lines.push_back(line);
                }
                monkeys.emplace_back(lines, worry_divisor);
            }
            this->common_denominator = accumulate(monkeys.begin(), monkeys.end(), 1, [](int acc, const Monkey& monkey){ return acc * monkey.divisor; });
        }

        void inspect (int monkey_id) {
            Monkey& monkey = monkeys[monkey_id];
            while( !monkey.items_held.empty() ) {
                monkey.inspections++;
                u_int64_t second;
                u_int64_t item = monkey.items_held.front();
                monkey.items_held.pop_front();
                try { second = stoi(monkey.second_operand) ; }
                catch (invalid_argument& e) { second = item; }
                item = available_operations.at(monkey.operation)(item, second);
                item = round(item / monkey.worry_divisor);
                item = item % common_denominator;
                int monkey_num = monkey.index_monkeys_available[item % monkey.divisor == 0];
                monkeys[monkey_num].items_held.push_back(item);
            }
        }

        void play(int rounds){
            for(int i=0; i < rounds; i++){
                for(int j=0; j < monkeys.size(); j++){
                    this->inspect(j);
                }
            }
        }

        void calculate_monkey_business(){
            sort(monkeys.begin(), monkeys.end(), [](const Monkey& a, const Monkey& b){ return a.inspections > b.inspections; });
            u_int64_t monkey_business_level = monkeys[0].inspections * monkeys[1].inspections ;
            for (const auto &monkey : monkeys) {
                cout << monkey.inspections << " " ;
            } cout << endl;
            cout << "Monkey business level =  " << monkeys[0].inspections << " * " << monkeys[1].inspections << " = " << monkey_business_level << endl;
        }
};



void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(11);
    MonkeyGame game(input, 3);
    cout << game.common_denominator << endl;
    game.play(20);
    game.calculate_monkey_business();
    
}


void parte2() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(11);
    int part = 2;
    MonkeyGame game(input, 1);
    game.play(10000);
    game.calculate_monkey_business();
}


int main () {
    cout << "Dia 11" << endl;
    parte1();
    parte2();
    return 0;
}