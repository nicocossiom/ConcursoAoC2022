// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <aocutils.h>
#include <set>
#include <functional>
#include <queue>

using namespace std;

class XYZ {
    public:
        int x;
        int y;
        int z;
        bool visited = false;
        XYZ(int x, int y, int z) : x(x), y(y), z(z){}
        XYZ() : x(0), y(0), z(0){}

        friend ostream& operator<<(ostream& os, const XYZ& xyz) {
            os << xyz.x << " " << xyz.y << " " << xyz.z;
            return os;
        }

        bool operator==(const XYZ &other) const {
            return (this->x == other.x && this->y == other.y && this->z == other.z);
        }

        // make this class work with vectors
        bool operator<(const XYZ &other) const {
            if (this->x < other.x) return true;
            if (this->x > other.x) return false;
            if (this->y < other.y) return true;
            if (this->y > other.y) return false;
            return this->z < other.z;
        }
        bool operator>(const XYZ &other) const {
            if (this->x > other.x) return true;
            if (this->x < other.x) return false;
            if (this->y > other.y) return true;
            if (this->y < other.y) return false;
            return this->z > other.z;
        }
        bool operator<=(const XYZ &other) const {
            return !(*this > other);
        }
        bool operator>=(const XYZ &other) const {
            return !(*this < other);
        }
        bool operator!=(const XYZ &other) const {
            return !(*this == other);
        }
}; 

class ElevationMap{
    public:
        XYZ destination;
        XYZ starting_point;

        vector<vector<XYZ>> map;

        explicit ElevationMap (fstream& input){
            string line;
            int i = 0; 
            while (getline(input, line)) {
                vector<XYZ> row;
                for(int j = 0; j < line.length(); j++){
                    switch (line[j])
                    {
                    case 'E':
                        this->destination = XYZ(i, j, 'z');
                        row.emplace_back(i, j, 'z');
                        break;
                    case 'S':
                        starting_point = XYZ(i, j, 'a');
                        row.emplace_back(i, j, 'a');
                        break;
                    default:
                        row.emplace_back(i, j, line[j]);
                        break;
                    }
                }
                map.push_back(row); 
                i++; 
            }
        }

        vector<XYZ> getNeighbors(const XYZ &current_pos, bool reverse = false){
            vector<XYZ> neighbors;
            vector<pair<int, int>> directions = {{0,1}, {0,-1}, {1,0}, {-1,0}};
            for (auto [x, y] : directions){
                int new_x = current_pos.x + x;
                int new_y = current_pos.y + y;
                if(0 <= new_x && new_x < map.size() && 0 <= new_y && new_y < map[0].size()){
                    if(!reverse && map[new_x][new_y].z <= current_pos.z + 1)
                            neighbors.push_back(map[new_x][new_y]);
                    else if(reverse && map[new_x][new_y].z >= current_pos.z - 1)
                            neighbors.push_back(map[new_x][new_y]);
                }
                    
            }
            return neighbors;
        }

        /**
         * Shortest path from start to destination moving in each step one elevation unit up at most.
         * 
         * @return Shortest path from start to destination moving in each step one elevation unit up at most.
         */
        int shortestPath1Level(const function<bool(XYZ, XYZ)>& stop_condition, bool reverse=false){
            queue<pair<int, XYZ>> stack;
            set<XYZ> visited;
            stack.push({0, reverse ? destination: starting_point});
            while(! stack.empty() ){
                auto [steps, current_pos] = stack.front();
                stack.pop();
                if(visited.insert(current_pos).second){
                    if(stop_condition(current_pos, destination))
                        return steps;
                    // cout << "Current pos: " << current_pos << endl;
                    vector<XYZ> neighbors = getNeighbors(current_pos, reverse);
                    for(const auto& neighbor : neighbors){
                        stack.push({steps+1, neighbor});
                        // cout << "\t" << "Neighbor: " << neighbor << endl;
                    }
                }
            }
            return -1;
        }
    
}; 

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(12);
    ElevationMap map = ElevationMap(input);
    // map.print();
    int shortest_path = map.shortestPath1Level([](XYZ a, XYZ b){return a == b;});
    cout << "Shortest path: " << shortest_path << endl;
}


void parte2() {
    cout << "Parte 2" << endl;
    fstream input = get_input_stream(12);
    ElevationMap map = ElevationMap(input);
    // map.print();
    int shortest_path = map.shortestPath1Level([](XYZ a, XYZ b){return a.z == 'a';}, true);

    cout << "Shortest path: " << shortest_path << endl;
}

int main () {
    cout << "Dia 12" << endl;
    // parte1();
    parte2();
    return 0;
}