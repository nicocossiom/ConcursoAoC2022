// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;


typedef priority_queue<int, vector<int>, greater<int> > pq;

class FixedSizePriorityQueue
    : public pq{

    public:
    int max_size;

    FixedSizePriorityQueue(int max_size): max_size(max_size) {}
    
    bool push(int x) {
        if (size() < max_size) {
            pq::push(x);
            return true;
        }
        if (size() == max_size && size() != 0 && x > top()) {
            pop();
            pq::push(x);
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

int main() {
    FixedSizePriorityQueue q(3);    
    string line;
    int total_cal = 0;
    fstream input_file ("input2", ios::in);
    while (getline(input_file, line)) {
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
    return 0;
}
