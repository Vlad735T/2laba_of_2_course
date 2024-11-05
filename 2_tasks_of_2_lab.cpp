#include <iostream>
#include <string>
#include "structures/set.h"
#include "structures/vector.h"
using namespace std;


struct user_command{
    string command;
    string name_structure;
    string value_fir = "null";
};


void parse_command(const string& query, user_command* cmd){
    string current = query;
    size_t pos = current.find(" ");
    if (pos != string::npos){

        cmd->command = current.substr(0, pos);
        current = current.substr(pos + 1);
        pos = current.find(" ");
        if (pos != string::npos){

            cmd->name_structure = current.substr(0, pos);
            current = current.substr(pos + 1);
            pos = current.find(" ");
            if (pos != string::npos){

                cmd->value_fir = current.substr(0, pos);
            } else {
                cmd->value_fir = current;
            }
        } else {
            cmd->name_structure = current;
        }
    } else {
        cmd->command = current;
    }
}


void process_command(const user_command& cmd, const string& name_file, const string& structure_name){

    if (structure_name == "set"){

        set<string> set;
        set.load_from_file(name_file, cmd.name_structure);
        if (cmd.command == "SETADD"){
            set.SPUSH(cmd.value_fir);
            set.save_to_file(name_file, cmd.name_structure);
        }
        else if (cmd.command == "SETDEL"){
            set.SDEL(cmd.value_fir);
            set.save_to_file(name_file, cmd.name_structure);
        }
        else if (cmd.command == "SETAT"){
            cout << set.check(cmd.value_fir) << endl;
        }
        else if (cmd.command == "SPRINT"){
            set.print();
        }
    }
}


string extract_structure(const string& filename){
    size_t pos = filename.find(".");
    if (pos == string::npos){
        throw runtime_error("Error: Invalid file name. The format is expected file.structure.");
    }
    return filename.substr(pos + 1);
}


bool check_structure(const string& structure_name){
    Myvector<string> structure;
    structure.MPUSH("set");
    bool found = false;

    for (size_t i = 0; i < structure.size(); i++){
        string check = structure.MGET(i);

        if (structure_name == check){
            found = true;
            break;
        }
    }

    if (!found){
        cout << "Unknown structure: " << structure_name << "!\n";
        return false;
    }
    return true;
}


int main(int argc, char* argv[]){
    try{

        if (argc != 5){
            throw runtime_error("The number of arguments is incorrect. Use: ./main --file <filename> --query '<command>'");
        }

        string name_file = argv[2];
        string query = argv[4];

        string structure_name = extract_structure(name_file);

        if (!check_structure(structure_name)){
            cout << "Structure " << structure_name << " not found.\n";
            return 0;
        }

        user_command cmd;
        parse_command(query, &cmd);
        process_command(cmd, name_file, structure_name);
    } catch (const runtime_error& e){
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}