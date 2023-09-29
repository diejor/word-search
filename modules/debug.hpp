/*
    * debug.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * debug functions used in word search program
    * changelog:
        - 09/28/2023 - header files created
*/

#ifndef DEBUG_H
#define DEBUG_H

#include <string>

#include "global.hpp"

using namespace std;

// =----------   DEBUG FUNCTIONS   ----------=
namespace debug {

    // debug flags, if true the program will show debug messages
    namespace flags {
        const bool USER_INPUT = true; 
        const bool TRY_OPEN_FILE = true;
        const bool TRIM_WHITESPACE = false;
    }

    void user_input(string input_file_name) {
        if (flags::USER_INPUT) {
            global::show_msg("DEBUG: user input: ", input_file_name);
        }
    }

    void open_file(string input_file_name) {
        if (flags::TRY_OPEN_FILE) {
            global::show_msg("DEBUG: trying to open file: ", input_file_name);
        }
    }

    void trim_whitespace(string input_file_name, int first_whspace_idx, int last_whspace_idx, string trimmed_input_file_name) {
        if (flags::TRIM_WHITESPACE) {
            global::show_msg("DEBUG: trimming whitespace from: ", input_file_name);
            global::show_msg("DEBUG: first whitespace index: ", to_string(first_whspace_idx));
            global::show_msg("DEBUG: last whitespace index: ", to_string(last_whspace_idx));
            global::show_msg("DEBUG: trimmed input file name: ", trimmed_input_file_name);
        }
    }
}
// =----------  END OF DEBUG FUNCTIONS   ----------=

#endif // DEBUG_H