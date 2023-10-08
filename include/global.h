/*
 * global.hpp
 * Diego R.R.
 * started: 09/28/2023
 * CS2337.501
 * global functions used in word search program
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
    void show_msg(const string& msg);
    void show_msg(const string& msg, const string& arg);
    void show_msg_noline(const string& msg);
    void show_msg_noline(const string& msg, const string& arg);
    void show_msg_doubleline(const string& msg);
    void show_msg_doubleline(const string& msg, const string& arg);

    bool is_str_in_vector(const string& str, const vector<string>& v);
    vector<string> difference(const vector<string>& v1, const vector<string>& v2);
    string trim_whitespace(const string& str);
    string to_lower(const string& str);
    bool contains(const string& str, const string& regex);
    string format_string(const string& str);

    int get_row(pair<int, int> pair);
    int get_col(pair<int, int> pair);
}

}  // namespace global

#endif  // GLOBAL_HPP