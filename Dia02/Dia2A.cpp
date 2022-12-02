// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
// import priority_queue

#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include <aocutils.h>

using namespace std;
int main() {
    string line;
    int max_cal = 0;
    
    fstream input = get_input_stream(1, ChallengePart::A);
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
    return 0;
}

// int main2() {
//     priority_queue<int> cal_q;
//     string line;
//     int total_cal = 0;
//     freopen("input1", "r", stdin);
//     cout << "Reading from file" << endl;
//     while (getline(cin, line)) {
//         if (line.empty()) {
//             cal_q.push(total_cal);
//             total_cal = 0;
//         } else {
//             int current_cal = stoi(line);
//             total_cal += current_cal;
//         }
//     }
//     cout << cal_q.top() << endl;
//     return 0;
// }
