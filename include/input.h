/*
    * input-loader.h
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to load input file
    * changelog:
        - 09/28/2023 - header files created
*/

#include <fstream>
#include <string>

using namespace std;

#ifndef INPUT_LOADER_HPP
#define INPUT_LOADER_HPP

namespace input {
extern string get_user_input(const string& msg);
extern ifstream get_input_file();
}  // namespace input

namespace input::debug {
    void user_input(string input);
    void open_file(string file_name);
}  // namespace debug

namespace input::error {
    void file_extension();
    void opening_file();
}  // namespace error

#endif  // INPUT_LOADER_HPP