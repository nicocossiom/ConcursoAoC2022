// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <aocutils.h>

using namespace std;

void parte1() {
    cout << "Parte 1" << endl;
    string line;
    int max_cal = 0;
    
    fstream input = get_input_stream(1, 1);
    int current_cal = 0;

    while (getline(input, line)) {
        if (line.empty()) {
            if (current_cal > max_cal) {
                max_cal = current_cal;
            }
            current_cal = 0;
        } else {
            int cal_item = stoi(line);
            current_cal += cal_item;
        }
    }
    cout << max_cal << endl;
}




class FixedSizePriorityQueue
    : public priority_queue<int, vector<int>, greater<int> >{

    public:
    typedef priority_queue<int, vector<int>, greater<int> > super;
    int max_size;

    FixedSizePriorityQueue(int max_size): max_size(max_size) {}
    
    bool push(int x) {
        if (size() < max_size) {
            super::push(x);
            return true;
        }
        if (size() == max_size && size() != 0 && x > top()) {
            pop();
            super::push(x);
            return true;
        }
        return false;
    }

    vector<int> toVector() {
        vector<int> v = vector<int>();
        while (!empty()) {
            v.push_back(top());
            pop();
        }
        return v;
    }
};

void parte2() {
    cout << "Parte 2" << endl;
    FixedSizePriorityQueue q(3);    
    string line;
    int total_cal = 0;
    fstream input = get_input_stream(1, 2);
    while (getline(input, line)) {
        if (line.empty()) {
            q.push(total_cal);
            total_cal = 0;
        } else {
            int current_cal = stoi(line);
            total_cal += current_cal;
        }
    }
    q.push(total_cal);

    auto v = q.toVector();
    int sum = 0; 
    for (auto& val: v){
        sum += val;
    }
    cout << sum << endl;
}

int main () {
    cout << "Dia 1" << endl;
    parte1();
    parte2();
    return 0;
}