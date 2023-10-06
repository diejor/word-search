/*
 * global.hpp
 * Diego R.R.
 * started: 09/28/2023
 * CS2337.501
 * global functions used in word search program
 */


#include <iostream>
#include <string>

using namespace std;

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

namespace debug {
void adding_to_difference(string str);
void trim_whitespace(string input_file_name, int first_whspace_idx,
                     int last_whspace_idx, string trimmed_input_file_name);
}

namespace global {

// -----------------------------------------------
// =----------------- CONSTANTS -----------------=
namespace msgs {
const string WELCOME = "Welcome to the Movie Title Searcher!";

// input
const string ENTER_FILE_NAME = "* enter file name: ";
const string ENTER_FILE_NAME_AGAIN = "* enter file name again: ";
const string USING_FILE = "* using file: ";

// error
const string INVALID_EXTENSION =
    "Invalid file extension. Enter one of the following extensions: ";
const string PROGRAM_FAILED = "The program got the following error: ";

const string ANOTHER_SEARCH =
    "Do you want to search for another movie title? (yes/no): ";
const string INVALID_ANSWER = "Sorry I couldn't understand your answer.";
const string GOODBYE = "Thank you for using this word-search program!";
}  // namespace msgs

/*

*/
namespace debug_flags {
const bool CONTROL_FLOW = true;

// global functions
const bool ADDING_TO_DIFFERENCE = false;

// input loader flags
const bool USER_INPUT = false;
const bool TRY_OPEN_FILE = false;
const bool TRIM_WHITESPACE = false;

// parser flags
const bool EMPTY_FILE = false;
const bool TOKEN_LINE = false;
const bool IGNORING_COMMENT_LINE = false;
const bool SOUP_OF_LETTERS_DIM = false;
const bool SOUP_OF_LETTERS = false;
const bool MOVIE_TITLES_TO_SEARCH = false;

// word searcher flags
const bool MOVIE_TITLE_FORMATTED = false;
const bool MOVIE_TITLE_FOUND = false;
const bool MOVIE_TITLE_NOT_FOUND = false;
const bool SEARCH_LOC_STATE = false;
const bool SEARCH_DIR_STATE = false;
}  // namespace debug_flags
// =----------------- END OF CONSTANTS -----------------=
// ------------------------------------------------------

// ------------------------------------------------------
// =----------------- GLOBAL FUNCTIONS -----------------=
namespace fncs {

void show_msg(string msg) {
    cout << msg << endl;
}

void show_msg(string msg, string arg) {
    cout << msg << arg << endl;
}

void show_msg_noline(string msg) {
    cout << msg;
}

void show_msg_noline(string msg, string arg) {
    cout << msg << arg;
}

void show_msg_doubleline(string msg) {
    cout << msg << endl
         << endl;
}

void show_msg_doubleline(string msg, string arg) {
    cout << msg << arg << endl
         << endl;
}

/*
    Helper fuction of difference function.
*/
bool is_str_in_vector(string str, vector<string> v) {
    bool is_in_v = false;
    for (string str_in_v : v) {
        if (str == str_in_v) {
            is_in_v = true;
            break;
        }
    }
    return is_in_v;
}

/*
    Used to find the movies titles that were not found in the soup of letters.
*/
vector<string> difference(vector<string> v1, vector<string> v2) {
    vector<string> difference;
    for (string str_in_v1 : v1) {
        if (!is_str_in_vector(str_in_v1, v2)) {
            debug::adding_to_difference(str_in_v1);
            difference.push_back(str_in_v1);
        }
    }
    return difference;
}

/*
    Used to trim leading and trailing whitespaces from the user input.
*/
string trim_whitespace(string str) {
    int first = str.find_first_not_of(' ');
    int last = str.find_last_not_of(' ');
    string trimmed_str = str.substr(first, (last - first + 1));
    debug::trim_whitespace(str, first, last, trimmed_str);
    return trimmed_str;
}

string to_lower(string str) {
    string lower_case_str = "";
    for (char ch : str) {
        lower_case_str += tolower(ch);
    }
    return lower_case_str;
}

bool contains(string str, string regex) {
    return str.find(regex) != string::npos;
}

} // namespace functions
// =----------------- END OF GLOBAL FUNCTIONS -----------------=
// -------------------------------------------------------------

}  // namespace global

#endif  // GLOBAL_HPP


// -----------------------------------------------------
// =----------------- DEBUG ROUTINES ------------------=
void debug::adding_to_difference(string str) {
    if (global::debug_flags::ADDING_TO_DIFFERENCE) {
        global::fncs::show_msg("DEBUG: adding to difference: ", str);
    }
}

void debug::trim_whitespace(string input_file_name, int first_whspace_idx,
                     int last_whspace_idx, string trimmed_input_file_name) {
    if (global::debug_flags::TRIM_WHITESPACE) {
        global::fncs::show_msg("DEBUG: trimming whitespace from: ",
                               input_file_name);
        global::fncs::show_msg("DEBUG: first whitespace index: ",
                               to_string(first_whspace_idx));
        global::fncs::show_msg("DEBUG: last whitespace index: ",
                               to_string(last_whspace_idx));
        global::fncs::show_msg("DEBUG: trimmed input file name: ",
                               trimmed_input_file_name);
    }
}

// =----------------- END OF DEBUG ROUTINES ------------------=
// -----------------------------------------------------------