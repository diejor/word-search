/*
    Movie Title Searcher
    Diego R.R.
    started: 09/20/2023
    CS2337.501
    A program that searches words from a soup of letters
    Changelog:
        09/20/2023 - project started
        09/22/2023 - notes of the project added
        09/24/2023 - bottom-up design of the project started
        09/28/2023 - header files created
        09/29/2023 - parser.cpp defined
        09/30/2023 - search.cpp defined
        10/01/2023 - release version finished
    Notes:
        To see more information about the heat maps and the ppm asociated with it, see the ppm_stream.h file.
        field.h defines how heat maps are created.
*/

#include <fstream>
#include <string>
#include <vector>

#include "fields.h"
#include "global.h"
#include "input.h"
#include "output.h"
#include "parser.h"
#include "ppm_stream.h"
#include "search.h"

using namespace std;

// =---------- INIT APP ----------=
void welcome_user() { global::fncs::show_msg(global::msgs::WELCOME); }

void init_program() { welcome_user(); }
// =---------- END OF INIT APP ----------=

// =---------- RUN PROGRAM ----------=
bool answer_contains(const string &answer, const string &word) {
    string answer_lower = global::fncs::to_lower(answer);
    return global::fncs::contains(answer_lower, word);
}

bool invalid_answer(const string &answer_lower) {
    return !answer_contains(answer_lower, "y") && !answer_contains(answer_lower, "n");
}

void run_program();  // prototype for recursion

bool said_yes(const string &answer) {
    string answer_lower = global::fncs::to_lower(answer);
    return answer_contains(answer_lower, "y");
}

void ask_if_another(const string &msg) {
    string answer = input::get_user_input(msg);
    if (said_yes(answer)) {
        run_program();
    }
}

fields::Polarization decide_polarization_type() {
    string answer = input::get_user_input(global::msgs::WHAT_POLARIZATION_TYPE);
    if (answer_contains(answer, "normal"))
        return fields::Polarization::NORMAL;
    else if (answer_contains(answer, "complete"))
        return fields::Polarization::COMPLETE;
    else {
        return fields::Polarization::NONE;
    }
}

search::Direction decide_polarization_dir() {
    string answer = input::get_user_input(global::msgs::WHAT_POLARIZATION_DIR);
    if (answer_contains(answer, "se"))
        return search::Direction::SOUTH_EAST;
    else if (answer_contains(answer, "nw"))
        return search::Direction::NORTH_WEST;
    else if (answer_contains(answer, "ne"))
        return search::Direction::NORTH_EAST;
    else if (answer_contains(answer, "sw"))
        return search::Direction::SOUTH_WEST;
    else if (answer_contains(answer, "n"))
        return search::Direction::NORTH;
    else if (answer_contains(answer, "s"))
        return search::Direction::SOUTH;
    else if (answer_contains(answer, "e"))
        return search::Direction::EAST;
    else if (answer_contains(answer, "w"))
        return search::Direction::WEST;
    else
        return search::Direction::NONE;
}

vector<vector<double>> create_soup_field(const vector<vector<char>> &soup,
                                         const vector<tuple<string, int, int, search::Direction>> &movies_found) {
    fields::Polarization polarization_type = fields::Polarization::NONE;
    search::Direction polarization_dir;
    string answer = input::get_user_input(global::msgs::ASK_IF_POLARIZED);
    if (!said_yes(answer)) {
        return fields::universal(soup, movies_found, search::Direction::NONE, polarization_type);
    } else {
        polarization_type = decide_polarization_type();
        polarization_dir = decide_polarization_dir();
        return fields::universal(soup, movies_found, polarization_dir, polarization_type);
    }
}

void ask_if_heat_map(const vector<tuple<string, int, int, search::Direction>> &movies_found,
                     const vector<vector<char>> &soup) {
    string answer = input::get_user_input(global::msgs::ASK_IF_HEAT_MAP);
    if (said_yes(answer)) {
        output::separate();
        vector<vector<double>> soup_field = create_soup_field(soup, movies_found);
        ppm_stream::create_heat_map(soup_field);
        ask_if_heat_map(movies_found, soup);
    }
}

void run_program() {
    ifstream input_file = input::get_input_file();
    output::separate();

    // parse input file
    vector<vector<char>> soup = parser::soup_letters(input_file);
    vector<string> movies = parser::movies_to_search(input_file);

    // display soup
    output::soup(soup);
    output::separate();

    // search and display movies found
    vector<tuple<string, int, int, search::Direction>> movies_found = search::movies_in_soup(soup, movies);
    output::movies_found(movies_found);
    output::separate();

    vector<string> movies_title_found =
        search::unzip_titles(movies_found);
    vector<string> movies_not_found =
        global::fncs::difference(movies, movies_title_found);

    output::movies_not_found(movies_not_found);
    output::separate();

    ask_if_heat_map(movies_found, soup);

    ask_if_another(global::msgs::ANOTHER_SEARCH);
    output::separate();
}
// =---------- END OF RUN PROGRAM ----------=

// =---------- FINALIZE APP ----------=
void finalize_word_search() {
    output::say_goodbye();  // :D
}
// =---------- END OF FINALIZE APP ----------=

// =------------ BODY OF THE PROGRAM ------------=
int main() {
    init_program();
    output::separate();
    run_program();
    finalize_word_search();
    return 0;
}
// =------------ END OF BODY ------------=