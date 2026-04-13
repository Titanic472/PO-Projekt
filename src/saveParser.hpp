#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <map>

#include "vector2.hpp"
#include "parserConfig.hpp"

using namespace std;

class SaveParser{
    fstream file;
    public:

    // save functions
    void create_file(Vector2 world_size);


    void add_entry(string key, string type, string value);


    void add_string_entry(string value);


    void start_category(string category_name);


    void end_category();


    // load functions
    // file is loaded sequentially so file can be loaded only once
    bool load_file(Vector2 world_size);


    void loadEntry(void* field, string key);


    bool jump_to_category(string category_name);


    bool load_entry_multiline(std::map<string, string>* entry_data);


    void close_file();


    private:

    bool file_exists(string file_name);


    fstream open_file(string file_name, ios_base::openmode mode);


    string get_next_value_from_string(string &str);


    void loadField(void* field, string type, string value);
};


// struct file_entry{
//     string key;
//     string type;
//     string value;
//     // int isHeader;
// } ;