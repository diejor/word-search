/*
    * input-loader.h
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to load input file
    * changelog:
        - 09/28/2023 - header files created
*/

#ifndef INPUT_LOADER_HPP
#define INPUT_LOADER_HPP

#include <fstream>
#include <string>
#include <vector>

#include "global.hpp"

using namespace std;
using namespace global;

namespace input_loader {

    namespace msgs {
        const string ENTER_FILE_NAME = "enter file name: ";
        const string ENTER_FILE_NAME_AGAIN = "enter file name again: ";
    }


    string get_user_input() {
        string input;
        getline(cin, input);
        string no_leading_preceding_whitespace = global::trim_whitespace(input);
        return no_leading_preceding_whitespace;
    }

    string get_file_name_validated() {
        string input_file_name;
        do {
            show_msg_noline(msgs::ENTER_FILE_NAME);

            // user input without whitespaces
            input_file_name = get_user_input();
            debug::user_input(input_file_name);

            if (!valid_extensions::has(input_file_name))
                error::file_extension(input_file_name);
        } while (!valid_extensions::has(input_file_name));
        return input_file_name;
    }

    ifstream get_input_file();

    ifstream try_open_file(string input_file_name) {
        debug::open_file(input_file_name);
        ifstream input_file;
        input_file.open(input_file_name);
        if (!input_file.good()) {
            error::failed_opening_file(input_file_name);
            // recursive call to retrieve_input_file()
            input_file = get_input_file();
        }
        return input_file;
    }

    ifstream get_input_file() {
        ifstream input_file;
        string input_file_name = get_file_name_validated();
        input_file = try_open_file(input_file_name);
        return input_file;
    }
} // namespace input_loader

#endif // INPUT_LOADER_HPP