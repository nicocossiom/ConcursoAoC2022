// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <aocutils.h>
using namespace std;

class XY {
    public:
        int x;
        int y;
        XY(int x, int y) : x(x), y(y){}
    
        bool isAdjacent(const XY other) {
            return (abs(this->x - other.x) <= 1 && abs(this->y - other.y) <= 1);
        }
        
        void move1Unit(char direction) {
            switch (direction) {
                case 'U':
                    y++;
                    break;
                case 'D':
                    y--;
                    break;
                case 'L':
                    x--;
                    break;
                case 'R':
                    x++;
                    break;
                default: cout << "Error" << endl; break;
            }
        }

        bool operator==(const XY &other) const {
            return (this->x == other.x && this->y == other.y);
        }
        bool operator!=(const XY &other) const {
            return !(*this == other);
        }
        bool operator<(const XY &other) const {
            if (this->x < other.x) return true;
            if (this->x > other.x) return false;
            return this->y < other.y;
        }
        bool operator>(const XY &other) const {
            if (this->x > other.x) return true;
            if (this->x < other.x) return false;
            return this->y > other.y;
        }
        bool operator<=(const XY &other) const {
            return !(*this > other);
        }
        bool operator>=(const XY &other) const {
            return !(*this < other);
        }
        // to string method
        friend ostream& operator<<(ostream& os, const XY& xy) {
            os << "(" << xy.x << ", " << xy.y << ")";
            return os;
        }
};

void move(vector<XY>& rope, char direction) {
    int num = 0; 
    rope.begin()->move1Unit(direction);
    while(num < rope.size()-1) {
        XY head = rope[num];
        XY tail = rope[num+1];
        if (head.isAdjacent(tail)) break; 
        int new_x = (head.x == tail.x ? 0 : (head.x - tail.x) / abs(head.x - tail.x)) + tail.x;
        int new_y = (head.y == tail.y ? 0 : (head.y - tail.y) / abs(head.y - tail.y)) + tail.y;
        rope[num+1] = {new_x, new_y};
        num++;
    }
}

void parteX(int size_of_rope){
    fstream input = get_input_stream(9);
    string line;
    vector<XY> rope (size_of_rope, {0, 0});
    set<XY> tail_visited;
    while (getline(input, line)) {
        char direction = line[0];
        int steps = stoi(line.substr(2));
        while(steps-- > 0) {
            move(rope, direction);
            tail_visited.insert(rope.back());
        }
    }
    
    cout << "Tail visited: " << tail_visited.size() << " distinct positions"<< endl;
}

void parte1() {
    cout << "Parte 1" << endl;
    parteX(2);
}
void parte2() {
    cout << "Parte 2" << endl;
    parteX(10);
}
int main () {
    cout << "Dia 9" << endl;
    parte1();
    parte2();
    return 0;
}