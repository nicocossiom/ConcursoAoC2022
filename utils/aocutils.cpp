// Copyright (c) 2022 "Nicolas Cossio Miravalles"
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT


#include <aocutils.h>
#include <iostream>
#include <fstream>  
#include <fmt/core.h>
using namespace std;

const string proyect_location = "/Users/pepperonico/code/upm/ConcursoAoC2022";

string get_input_path(int day_of_challenge, int part_of_challenge) {
    string file_name = fmt::format("{}/inputs/inputDia{}{}", proyect_location, day_of_challenge,
        part_of_challenge == 1 ? "A" : "B");
    return file_name;
}

// make a function that returns a stream to the input file using the day and part of the challenge
fstream get_input_stream(int day_of_challenge,int part_of_challenge) {
    string input_path = get_input_path(day_of_challenge, part_of_challenge); 
    fstream f ( input_path, ios::in); 
    return f;
}