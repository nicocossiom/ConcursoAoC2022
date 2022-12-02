// Copyright (c) 2022 "Nicolas Cossio Miravalles"
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#ifndef AOCUTILS_H
#define AOCUTILS_H
#include <string>
#include <iostream>
#include <fstream>  
using std::string;
// declare enum with 2 options for the part of challenge

std::fstream get_input_stream(int day_of_challenge,int part_of_challenge); 
#endif // AOCUTILS_H