
#include <string>
#include <vector>

#include "global.hpp" 

using namespace std;
using namespace global;

// ------------------------------------------------------
// =----------------- GLOBAL FUNCTIONS -----------------=

void global::fncs::show_msg(string msg) {
    cout << msg << endl;
}

void global::fncs::show_msg(string msg, string arg) {
    cout << msg << arg << endl;
}

void global::fncs::show_msg_noline(string msg) {
    cout << msg;
}

void global::fncs::show_msg_noline(string msg, string arg) {
    cout << msg << arg;
}

void global::fncs::show_msg_doubleline(string msg) {
    cout << msg << endl
         << endl;
}

void global::fncs::show_msg_doubleline(string msg, string arg) {
    cout << msg << arg << endl
         << endl;
}

/*
    Helper fuction of difference function.
*/
bool global::fncs::is_str_in_vector(string str, vector<string> v) {
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
vector<string> global::fncs::difference(vector<string> v1, vector<string> v2) {
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
string global::fncs::trim_whitespace(string str) {
    int first = str.find_first_not_of(' ');
    int last = str.find_last_not_of(' ');
    string trimmed_str = str.substr(first, (last - first + 1));
    debug::trim_whitespace(str, first, last, trimmed_str);
    return trimmed_str;
}

string global::fncs::to_lower(string str) {
    string lower_case_str = "";
    for (char ch : str) {
        lower_case_str += tolower(ch);
    }
    return lower_case_str;
}

bool global::fncs::contains(string str, string regex) {
    return str.find(regex) != string::npos;
}

// =----------------- END OF GLOBAL FUNCTIONS -----------------=
// -------------------------------------------------------------

// -----------------------------------------------------
// =----------------- DEBUG ROUTINES ------------------=
namespace debug{
void adding_to_difference(string str) {
    if (debug_flags::ADDING_TO_DIFFERENCE) {
        fncs::show_msg("DEBUG: adding to difference: ", str);
    }
}

void trim_whitespace(string input_file_name, int first_whspace_idx,
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
}  // namespace debug

// =----------------- END OF DEBUG ROUTINES ------------------=
// -----------------------------------------------------------