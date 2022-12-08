// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <aocutils.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <ranges>
#include <boost/range/adaptor/reversed.hpp>


using namespace std;

using Matrix = vector<vector<int>>;


void matrix_printer(Matrix matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
        cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Matrix transpose_matrix(Matrix matrix_to_transpose){
    Matrix trees_matrix_transposed;
    for(int i=0; i < matrix_to_transpose.size(); i++) {
        vector<int> tree_column;
        for(int j=0; j < matrix_to_transpose[0].size(); j++) {
            tree_column.push_back(matrix_to_transpose[j][i]);
        }
        trees_matrix_transposed.push_back(tree_column);
    }
    return trees_matrix_transposed;
}

Matrix create_matrix_from_input(fstream& input) {
    string line;
    Matrix trees_matrix;
    while (getline(input, line)) {
        vector<int> tree_line;
        for (char c : line) {
        tree_line.push_back(c - '0');
        }
        trees_matrix.push_back(tree_line);
    }
    return trees_matrix;
}

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(8);
    Matrix trees_matrix = create_matrix_from_input(input);
    auto trees_matrix_transposed = transpose_matrix(trees_matrix);
    int visible_trees = trees_matrix[0].size() * 2 + trees_matrix.size() * 2 -4; // outer border
    cout << "Outer border: " << visible_trees << endl;
    matrix_printer(trees_matrix);
    matrix_printer(trees_matrix_transposed);
    for (int i = 1; i < trees_matrix.size()-1; i++) {
        auto row = trees_matrix[i];
        for(int j = 1; j < row.size()-1; j++) {
            int elem = trees_matrix[i][j];
                auto col = trees_matrix_transposed[j];
                int max_in_row_to_left = *max_element(row.begin(), row.begin() + j );
                int max_in_row_to_right = *max_element(row.begin() + j + 1, row.end());
                int max_in_col_left = *max_element(col.begin(), col.begin() + i );
                int max_in_col_right = *max_element(col.begin() + i + 1, col.end());
                cout << "(" << i << "," << j << "): " << elem << " Maxs: " << max_in_row_to_left << " " << max_in_row_to_right << " " << max_in_col_left << " " << max_in_col_right;
                vector <int> maxs = {max_in_row_to_left, max_in_row_to_right, max_in_col_left, max_in_col_right};
                for (auto max: maxs) { 
                    if (elem > max) {
                        visible_trees++; 
                        cout << " <-- Visible tree";
                        break;
                    }
                }
                cout << endl;
        }
    }
    cout << "Total visible trees: " << visible_trees << endl;
}

int rate(vector<int>& vec, vector<int>::iterator& it) {
    if (it == vec.end()) 
        return vec.size();
    
    return  abs(distance(vec.begin(), it)) + 1;
}

int score(vector<int>& row, vector<int>& col, int i, int j){
    int elem = row[j];
    auto first_bigger_than_elem = [elem](int x) { return x >= elem; };
    vector<int> left_half(row.begin(), row.begin() + j);
    vector<int> right_half(row.begin() + j + 1, row.end());
    vector<int> up_half(col.begin(), col.begin() + i);
    vector<int> down_half(col.begin() + i + 1, col.end());
    reverse(left_half.begin(), left_half.end());
    reverse(up_half.begin(), up_half.end());
    auto left_it = find_if(left_half.begin(), left_half.end(), first_bigger_than_elem);
    auto right_it = find_if(right_half.begin(), right_half.end(), first_bigger_than_elem);
    auto up_it = find_if(up_half.begin(), up_half.end(), first_bigger_than_elem);
    auto down_it = find_if(down_half.begin(), down_half.end(), first_bigger_than_elem);
    return rate(left_half, left_it) * rate(right_half, right_it) * rate(up_half, up_it) * rate(down_half, down_it);
}

void parte2() {
    cout << "Parte 2 " << endl;
    fstream input = get_input_stream(8);
    Matrix trees_matrix = create_matrix_from_input(input);
    int best_scenic_score = 0; 
    auto trees_matrix_transposed = transpose_matrix(trees_matrix);
    for (int i = 1; i < trees_matrix.size()-1; i++) {
        auto row = trees_matrix[i];
        for(int j = 1; j < row.size()-1; j++) {
            auto col = trees_matrix_transposed[j];
            int score_val = score(row, col, i, j);
            if(score_val > best_scenic_score) {
                best_scenic_score = score_val;
            }
        }
    }
    cout << "Best scenic score: " << best_scenic_score << endl;
}



void prueba(){
    // create a sample vector of int
    vector<int> v = {9, 2, 6, 4, 5, 7, 6, 8 , 10};
    int current_i = 4;
    int current = *(v.begin()+4);
    // copy the vector and reverse it
    vector<int> v2(current_i);
    copy(v.begin(), v.begin()+current_i, v2.begin());
    reverse(v2.begin(), v2.end());
    // get the first element bigger than current in v2
    auto it = find_if(v2.begin(), v2.end(), [current](int i){return i > current;});
    auto it2 = find_if(v.begin()+current_i, v.end(), [current](int i){return i > current;});
    // print the results
    cout << "Current: " << current << endl;
    cout << "Left: " << *it << endl;
    cout << "Right: " << *it2 << endl;

}

int main() {
    cout << "Dia X" << endl;
    // parte1();
    // prueba();
    parte2();
    return 0;
}