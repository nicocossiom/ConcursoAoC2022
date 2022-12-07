// Copyright (c) 2022 "Nicolas Cossio Miravalles"
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <aocutils.h>
#include <regex>

using namespace std;
enum IOSItemType {IFILE, IDIRECTORY};

class IOSItem{   
    public:
        string name;
        IOSItemType type;
        int size;
        IOSItem* parent_item;
        vector<IOSItem*> files;
        vector<IOSItem*> directories;
        IOSItem* directory;
        IOSItem(string name, int size, IOSItemType type, IOSItem* cwd)
        : name(name), type(type), size(size)  {
            if (type == IDIRECTORY){
                if(cwd != nullptr){
                    parent_item = cwd;
                    cwd->directories.push_back(this);
                }
            }else{ // IFILE
                directory = cwd;
                cwd->files.push_back(this);
                cwd->size += size;
                cwd->update_parent_size(size);
            }
        }
        void update_parent_size(int size){
            if (parent_item != nullptr){
                parent_item->size += size;
                parent_item->update_parent_size(size);
            }
        }
        
};

void process_ls(vector<string>& command_ouput, IOSItem* cwd){
    for (auto& line : command_ouput){
        regex dir_regex ("dir (.*)");
        regex file_regex ("\\d+ (.*)");
        smatch dir_match;
        smatch file_match;
        if (regex_search(line, dir_match, dir_regex)){
            new IOSItem(dir_match[1], 0, IDIRECTORY, cwd);
        }
        else if (regex_search(line, file_match, file_regex)){
            new IOSItem (file_match[1], stoi(file_match[0].str()), IFILE, cwd);
        }
    }
}

bool next_line_if_not_command(fstream& input, string& line){
    auto len = (int)input.tellg();
    auto res = getline(input, line).eof();
    if (line[0]=='$')  {
        input.seekg(len ,std::ios_base::beg);
        return false;
    }
    return !res;
}

IOSItem* construct_fs(fstream& input){
    string line;
    vector<string> command_ouput;
    IOSItem* root_dir = new IOSItem("/", 0, IDIRECTORY, nullptr);
    IOSItem* cwd = root_dir;
    getline(input, line); //skip first line it's root dir anyways
    while (getline(input, line)) {
        if (line[0]=='$'){
            if (line.length() == 4){ // ls
                while(next_line_if_not_command(input, line)) 
                    command_ouput.push_back(line);
                if(input.eof()) command_ouput.push_back(line); // feo, if ls is last command last output line is not read by next_line_if_not_command
                process_ls(command_ouput,cwd);
                command_ouput.clear();
            }
            else { //cd 
                string dir_to_move_to = (line.substr(5));
                if(dir_to_move_to == ".."){
                    cwd = cwd->parent_item;
                    continue;
                }
                if(dir_to_move_to == "/"){
                    cwd = root_dir;
                    continue;
                }
                // check if new dir already in cwd contents
                bool init = false;
                for (const auto& item : cwd->directories){
                    if(item->name == dir_to_move_to){
                        cwd = item;
                        init = true;
                        break;
                    }
                }
            }
        }
    }
    return root_dir;
}

void traverse_tree(IOSItem* item, int& total_size){
    // cout << item->name << " " << item->size << endl;
    if(item->size < 100000) {
        total_size += item->size;
    }
    for (auto& dir : item->directories){
        traverse_tree(dir, total_size);
    }
}

void parte1() {
    cout << "Parte 1" << endl;
    fstream input = get_input_stream(7, 1);
    IOSItem* root_dir = construct_fs(input);
    int total_size = 0;
    traverse_tree(root_dir, total_size);
    cout << "Total sum of sizes of items with size < 100000 is: " << total_size << endl;
}
#define AVAILABLE_SIZE 70000000
#define SIZE_OF_UPDATE 30000000
void get_mininum_dir(IOSItem* item, int& best_size, int& size_of_update){
    cout << item->name << " " << item->size << endl;
    if(item->size >= size_of_update && item->size < best_size) {
        best_size = item->size;
    }
    for (auto& dir : item->directories){
        if(dir->size > size_of_update){
            get_mininum_dir(dir, best_size, size_of_update);
        }
    }
}

void parte2() {
    cout << "Parte 2" << endl;
    string line; 
    fstream input = get_input_stream(7, 1);
    IOSItem* root_dir = construct_fs(input);
    int needed_size = abs(AVAILABLE_SIZE - root_dir->size - SIZE_OF_UPDATE);
    cout << "Need to delete size: " << abs(needed_size) << endl;
    int total_size = root_dir->size;
    get_mininum_dir(root_dir, total_size, needed_size);
    cout << "Size of smallest directory > " << needed_size << " is: " << total_size << endl;
}


int main () {
    cout << "Dia 7" << endl;
    parte1();
    parte2();
    return 0;
}