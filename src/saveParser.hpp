#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

#include "vector2.hpp"
#include "parserConfig.hpp"

using namespace std;

class SaveParser{
    fstream file;
    public:

    void create_file(Vector2 world_size);


    void add_entry(string key, string type, string value);


    void add_string_entry(string value);


    void start_category(string category_name);


    void end_category();


    void close_file();


    // void save(Vector2 world_size);


    // void load(Vector2 world_size);


    // bool read_next_entry(file_entry* entry);


    private:

    bool file_exists(string file_name);


    fstream open_file(string file_name, ios_base::openmode mode);

};


// struct file_entry{
//     string key;
//     string type;
//     string value;
//     // int isHeader;
// } ;