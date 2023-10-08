
#include <string>
#include <vector>

#include "global.h"

using namespace std;
using namespace global;

namespace debug {
    void adding_to_difference(const string& str);
    void trim_whitespace(const string& input_file_name, int first_whspace_idx,
                         int last_whspace_idx, string trimmed_input_file_name);
    void format_string(string movie_title, string formatted);
}  // namespace debug

// ------------------------------------------------------
// =----------------- GLOBAL FUNCTIONS -----------------=

void global::fncs::show_msg(const string& msg) {
    cout << msg << endl;
}

void global::fncs::show_msg(const string& msg, const string& arg) {
    cout << msg << arg << endl;
}

void global::fncs::show_msg_noline(const string& msg) {
    cout << msg;
}

void global::fncs::show_msg_noline(const string& msg, const string& arg) {
    cout << msg << arg;
}

void global::fncs::show_msg_doubleline(const string& msg) {
    cout << msg << endl
         << endl;
}

void global::fncs::show_msg_doubleline(const string& msg, const string& arg) {
    cout << msg << arg << endl
         << endl;
}

/*
    Helper fuction of difference function.
*/
bool global::fncs::is_str_in_vector(const string& str, const vector<string>& v) {
    bool is_in_v = false;
    for (const string& str_in_v : v) {
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
vector<string> global::fncs::difference(const vector<string>& v1, const vector<string>& v2) {
    vector<string> difference;
    for (const string& str_in_v1 : v1) {
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
string global::fncs::trim_whitespace(const string& str) {
    unsigned int first = str.find_first_not_of(' ');
    unsigned int last = str.find_last_not_of(' ');
    string trimmed_str = str.substr(first, (last - first + 1));
    debug::trim_whitespace(str, first, last, trimmed_str);
    return trimmed_str;
}

string global::fncs::to_lower(const string& str) {
    string lower_case_str;
    for (char ch : str) {
        lower_case_str += tolower(ch);
    }
    return lower_case_str;
}

bool global::fncs::contains(const string& str, const string& regex) {
    return str.find(regex) != string::npos;
}

/*
    This function is needed to make the pattern matching of the movie title case
   insensitive, that way the movie title string is succesfully compared
   one-to-one with the soup of letters.
*/
string global::fncs::format_string(const string& movie_title) {
    string formatted = "";
    for (char letter: movie_title) {
        if (isalpha(letter)) {
            char upper_letter = toupper(letter);
            formatted.push_back(upper_letter);
        }
    }
    debug::format_string(movie_title, formatted);
    return formatted;
}

int global::fncs::get_row(pair<int, int> pair) {
    return pair.first;
}

int global::fncs::get_col(pair<int, int> pair) {
    return pair.second;
}

// -----------------------------------------------------
// =----------------- DEBUG ROUTINES ------------------=
    void debug::adding_to_difference(const string& str) {
        if (debug_flags::ADDING_TO_DIFFERENCE) {
            fncs::show_msg("DEBUG: adding to difference: ", str);
        }
    }

    void debug::trim_whitespace(const string& input_file_name, int first_whspace_idx,
                         int last_whspace_idx, string trimmed_input_file_name) {
        if (global::debug_flags::TRIM_WHITESPACE) {
            fncs::show_msg("DEBUG: trimming whitespace from: ",
                           input_file_name);
            fncs::show_msg("DEBUG: first whitespace index: ",
                           to_string(first_whspace_idx));
            fncs::show_msg("DEBUG: last whitespace index: ",
                           to_string(last_whspace_idx));
            fncs::show_msg("DEBUG: trimmed input file name: ",
                           trimmed_input_file_name);
        }
    }

    void debug::format_string(string movie_title, string formatted) {
        if (debug_flags::MOVIE_TITLE_FORMATTED) {
            fncs::show_msg("DEBUG: movie title: ", movie_title);
            fncs::show_msg("DEBUG: movie title formatted: ", formatted);
        }
    }
// =----------------- END OF DEBUG ROUTINES ------------------=
// -----------------------------------------------------------


// =----------------- END OF GLOBAL FUNCTIONS -----------------=
// -------------------------------------------------------------

