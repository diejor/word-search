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

#include "global.h"

using namespace std;
using namespace global;

#include <fstream>
#include <string>

#include "global.h"

using namespace std;

namespace input {
namespace debug {
void user_input(const string &input) {
    if (global::debug_flags::USER_INPUT) {
        fncs::show_msg("DEBUG: user input: ", input);
    }
}

void open_file(const string &input) {
    if (global::debug_flags::TRY_OPEN_FILE) {
        fncs::show_msg("DEBUG: trying to open file: ", input);
    }
}

void output_validation(const string &output_file_name, const string &output) {
    if (global::debug_flags::OUTPUT_VALIDATION) {
        fncs::show_msg("DEBUG: output file name: ", output_file_name);
        fncs::show_msg("DEBUG: output: ", output);
    }
}
}  // namespace debug

namespace error {
void file_extension() {
    global::fncs::show_msg(global::msgs::INVALID_EXTENSION);
}

void opening_file() {
}
}  // namespace error

namespace extensions {
const string EXTENSIONS[] = {".txt", ".ppm"};

bool has(const string &file_name, const string &extension) {
    return file_name.find(extension) != string::npos;
}

bool has(const string &file_name) {
    bool has_extension = false;
    for (const string &extension : EXTENSIONS) {
        if (has(file_name, extension)) {
            has_extension = true;
            break;
        }
    }
    return has_extension;
}

bool has_except(const string &file_name, const string &extension) {
    bool has_extension = false;
    for (const string &ext : EXTENSIONS) {
        if (has(file_name, ext) && ext != extension) {
            has_extension = true;
            break;
        }
    }
    return has_extension;
}
}  // namespace extensions

/*
    Basically a helper function of get_file_name_validated() that handles how
   the input is retrieved from the user.
*/
string get_user_input(const string &msg) {
    string input;
    global::fncs::show_msg_noline(msg);
    getline(cin, input);
    string no_leading_preceding_whitespace = global::fncs::trim_whitespace(input);
    debug::user_input(no_leading_preceding_whitespace);
    return no_leading_preceding_whitespace;
}

/*
    Validation of a file is checking if the file has a valid extension. This
   function is conjoined with get_user_input() to retrieve the file name from
   the user macking sure that the file name has a valid extension.

    If the file name doesn't have a valid extension the function handles the
   case by asking the user to enter the file name again.
*/
string get_file_name_validated() {
    string input_file_name = get_user_input(global::msgs::ENTER_FILE_NAME);

    while (!extensions::has(input_file_name)) {
        error::file_extension();
        input_file_name = get_user_input(global::msgs::ENTER_FILE_NAME_AGAIN);
    }
    return input_file_name;
}

const string DEFAULT_OUTPUT_EXTENSION = ".ppm";

string validate_output(const string &output_file_name) {
    string output = output_file_name;
    while (extensions::has_except(output_file_name, DEFAULT_OUTPUT_EXTENSION)) {
        error::file_extension();
        output = get_user_input(global::msgs::ENTER_PPM_FILE_NAME);
    }
    if (output.empty()) {
        output = "output" + DEFAULT_OUTPUT_EXTENSION;
    } else if (!extensions::has(output_file_name, DEFAULT_OUTPUT_EXTENSION)) {
        output += DEFAULT_OUTPUT_EXTENSION;
    }
    debug::output_validation(output_file_name, output);
    return output;
}

/*
    Function used in get_input_file() to assert that the file exists and open
   it.

    If the file doesn't exists, similarly to get_file_name_validated(), the
   function handles the case by asking the user to enter the file name again.

    The logic of this function is similar to get_file_name_validated(), perhaps
   with functional programming both functions could be merged into one.
*/
ifstream try_open_file(string input_file_name) {
    ifstream input_file;
    input_file.open(input_file_name);  // assert that the file exists
    while (!input_file.is_open()) {
        error::opening_file();
        input_file_name = get_user_input(global::msgs::ENTER_FILE_NAME_AGAIN);
        input_file.open(input_file_name);
    }
    return input_file;
}

/*
    This function is the main function of this module. It is used to retrieve
   the input file name from the user and return the ifstream object of the file.
*/
ifstream get_input_file() {
    ifstream input_file;
    string input_file_name = get_file_name_validated();
    input_file = try_open_file(input_file_name);
    global::fncs::show_msg(global::msgs::USING_FILE, input_file_name);
    return input_file;
}

}  // namespace input

#endif  // INPUT_LOADER_HPP