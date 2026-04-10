#include "saveParser.hpp"


void SaveParser::create_file(Vector2 world_size){
    file = open_file("saves/" + world_size.to_string() + ".save", ios::in | ios::out | ios::trunc);
}


void SaveParser::add_entry(string key, string type, string value){
    file << key << ":" << type << ":" << value << ";\n";
}


void SaveParser::add_string_entry(string value){
    if(value.back() == DataFormat::CATEGORY_END_HEADER)
        file << value << "\n";
    else
        file << value << DataFormat::CATEGORY_END_HEADER << "\n";
}


void SaveParser::start_category(string category_name){
    file << category_name << ":" << DataFormat::CATEGORY_START_HEADER << "\n";
}


void SaveParser::end_category(){
    file << DataFormat::CATEGORY_END_HEADER << "\n";
}


void SaveParser::close_file(){
    file.close();
}


bool SaveParser::file_exists(string file_name){
    ifstream file(file_name);
    return file.good();
}


fstream SaveParser::open_file(string file_name, ios_base::openmode mode){
    fstream file(file_name, mode);
    if (!file.is_open()) {
        cerr << "CAN'T OPEN FILE: " << file_name << endl;
        usleep(10000000);
        exit(1);
    }
    return file;
}



// void SaveParser::save(Vector2 world_size){
//     fstream file = open_file("saves/" + world_size.to_string(), ios::out | ios::trunc);

//     file << "world_size:V2:" << world_size.to_string() << ";\n";


//     file.close();
// }


// void SaveParser::load(Vector2 world_size){
// }
