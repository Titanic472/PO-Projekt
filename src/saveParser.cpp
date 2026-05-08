#include "saveParser.hpp"
#include "world.hpp"


void SaveParser::create_file(Vector2 world_size){
    string file_name = "saves/" + world_size.to_string() + ".save";
    file = open_file(file_name, ios::in | ios::out | ios::trunc);
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


string SaveParser::stringify_entry(string key, const char* type, string value) const{
    return key + DataFormat::VALUE_SEPARATOR + type + DataFormat::VALUE_SEPARATOR + value + DataFormat::ENTRY_SEPARATOR + "\n";
}


string SaveParser::stringify_entry(string key, char type) const{
    return key + DataFormat::VALUE_SEPARATOR + type + "\n";
}


void SaveParser::close_file(){
    file.close();
}


bool SaveParser::file_exists(string file_name){
    ifstream filee(file_name);
    return filee.good();
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


bool SaveParser::load_file(Vector2 world_size){
    string file_name = "saves/" + world_size.to_string() + ".save";
    if(!file_exists(file_name))
        return false;

    file = open_file(file_name, ios::in);
    return true;
}


void SaveParser::loadEntry(void* field, string key){
    string line;
    while(getline(file, line)){
        if(line.empty())
            continue;

        string entry_key = get_next_value_from_string(line);
        if(entry_key == key){
            string type = get_next_value_from_string(line);
            if(type[0] == DataFormat::CATEGORY_START_HEADER){
                World::get_renderer()->add_to_log("EXPECTED ENTRY BUT CATEGORY START FOUND: " + key);
                return;
            }
            string value = get_next_value_from_string(line);

            loadField(field, type, value);
            return;
        }
    }

    World::get_renderer()->add_to_log("ENTRY: \"" + key + "\" NOT FOUND IN FILE");

}


bool SaveParser::jump_to_category(string category_name){
    string line;
    while(getline(file, line)){
        if(line.empty())
            continue;

        string entry_key = get_next_value_from_string(line);
        if(entry_key == category_name){
            string type = get_next_value_from_string(line);
            if(type[0] != DataFormat::CATEGORY_START_HEADER){
                World::get_renderer()->add_to_log("EXPECTED CATEGORY START BUT ENTRY FOUND: " + category_name);
                return false;
            }
            return true;
        }
    }
    return false;
}


bool SaveParser::load_entry_multiline(std::map<string, string>* entry_data){
    string line;
    getline(file, line);

    if(line.empty() || line[0] == DataFormat::CATEGORY_END_HEADER)
        return false;
    else{
        (*entry_data)["type"] = get_next_value_from_string(line);
        if(line[0] != DataFormat::CATEGORY_START_HEADER)
            return false;
    }

    while(getline(file, line) && !line.empty() && line[0] != DataFormat::CATEGORY_END_HEADER){
        string key = get_next_value_from_string(line);
        get_next_value_from_string(line); // skip type for multiple values loading
        string value = get_next_value_from_string(line);

        (*entry_data)[key] = value;
    }
    return true;
}


// std::map<string, string>* SaveParser::load_next(){
//     std::map<string, string>* entry_data = new std::map<string, string>();

//     string line;
//     getline(file, line);

//     if(line.empty())
//         return entry_data;

//     entry_data->insert({"key", get_next_value_from_string(line)});
//     entry_data->insert({"type", get_next_value_from_string(line)});
//     if(entry_data->at("type")[0] == DataFormat::CATEGORY_START_HEADER){
//         return entry_data;
//     }
//     entry_data->insert({"value", get_next_value_from_string(line)});

//         string key = get_next_value_from_string(line);
//         string value = get_next_value_from_string(line);

//         (*entry_data)[key] = value;
//     }
//     return nullptr;
// }


string SaveParser::get_next_value_from_string(string &str){
    size_t pos = str.find(DataFormat::VALUE_SEPARATOR);

    // last values are not followed by value separator but entry separator instead
    if(pos == string::npos){
        pos = str.find(DataFormat::ENTRY_SEPARATOR);
    }
    string result = str.substr(0, pos);
    str = str.substr(pos + 1);
    return result;
}


// convert string value from file to given type
void SaveParser::loadField(void* field, string type, string value){
    if (type == DataFormat::TYPE_INT){
        *((int*)field) = stoi(value);
    }
    else if (type == DataFormat::TYPE_FLOAT){
        *((float*)field) = stof(value);
    }
    else if (type == DataFormat::TYPE_STRING){
        //strip from " if present
        if(value.front() == '\"' && value.back() == '\"'){
            value.pop_back();
            value.erase(value.begin());
        }
        *((string*)field) = value;
    }
    else if (type == DataFormat::TYPE_VECTOR2){
        *((Vector2*)field) = Vector2(value);
    }
    else{
        World::get_renderer()->add_to_log("UNKNOWN TYPE: " + type);
    }
}




// void SaveParser::save(Vector2 world_size){
//     fstream file = open_file("saves/" + world_size.to_string(), ios::out | ios::trunc);

//     file << "world_size:V2:" << world_size.to_string() << ";\n";


//     file.close();
// }


// void SaveParser::load(Vector2 world_size){
// }
