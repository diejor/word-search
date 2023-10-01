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

namespace input {

    /*
        Basically a helper function of get_file_name_validated() that handles how the input is retrieved from the user.
    */
    string get_user_input(string msg) {
        string input;
        global::show_msg_noline(msg);
        getline(cin, input);
        string no_leading_preceding_whitespace = global::trim_whitespace(input);
        global::debug::user_input(no_leading_preceding_whitespace);
        return no_leading_preceding_whitespace;
    }

    /*
        Validation of a file is checking if the file has a valid extension. This function is conjoined with get_user_input() to retrieve the file name from the user macking sure that the file name has a valid extension.

        If the file name doesn't have a valid extension the function handles the case by asking the user to enter the file name again.
    */
    string get_file_name_validated() {
        string input_file_name = get_user_input(global::msgs::ENTER_FILE_NAME);
        while (!global::valid_extensions::has(input_file_name)) {
            error::file_extension(input_file_name);
            input_file_name = get_user_input(global::msgs::ENTER_FILE_NAME_AGAIN);
        }
        return input_file_name;
    }

    /*
        Function used in get_input_file() to assert that the file exists and open it.

        If the file doesn't exists, similarly to get_file_name_validated(), the function handles the case by asking the user to enter the file name again.

        The logic of this function is similar to get_file_name_validated(), perhaps with functional programming both functions could be merged into one.  
    */
    ifstream try_open_file(string input_file_name) {
        ifstream input_file;
        input_file.open(input_file_name); // assert that the file exists
        while (!input_file.is_open()) {
            global::error::opening_file(input_file_name);
            input_file_name = get_user_input(global::msgs::ENTER_FILE_NAME_AGAIN);
            input_file.open(input_file_name);
        }
        return input_file;
    }

    /*
        This function is the main function of this module. It is used to retrieve the input file name from the user and return the ifstream object of the file.
    */
    ifstream get_input_file() {
        ifstream input_file;
        string input_file_name = get_file_name_validated();
        input_file = try_open_file(input_file_name);
        return input_file;
    }
} // namespace input

#endif // INPUT_LOADER_HPP