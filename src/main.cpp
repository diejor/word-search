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
        Even though the project physical structure is weird because header files include both private and public implementation, it is the best I could do to prevent creating extra directories that would confuse the grader.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../include/global.hpp"
#include "../include/input.hpp"
#include "../include/output.hpp"
#include "../include/parser.hpp"
#include "../include/search.hpp"

using namespace std;

// =---------- INIT APP ----------=
void welcome_user() { global::fncs::show_msg(global::msgs::WELCOME); }

void init_program() { welcome_user(); }
// =---------- END OF INIT APP ----------=

// =---------- RUN PROGRAM ----------=
bool invalid_answer(string answer_lower) {
    return !global::fncs::contains(answer_lower, "y") && !global::fncs::contains(answer_lower, "yes") &&
           !global::fncs::contains(answer_lower, "n") && !global::fncs::contains(answer_lower, "no");
}

void run_program();  // prototype for recursion
void ask_if_another_file() {
    string answer = input::get_user_input(global::msgs::ANOTHER_SEARCH);
    string answer_lower = global::fncs::to_lower(answer);
    do {
        if (global::fncs::contains(answer_lower, "y") || global::fncs::contains(answer_lower, "yes")) {
            run_program();
        }
        else if (global::fncs::contains(answer_lower, "n") ||
                   global::fncs::contains(answer_lower, "no")) {
            break;

        } 
        else {
            global::fncs::show_msg(global::msgs::INVALID_ANSWER);
            answer = input::get_user_input(global::msgs::ANOTHER_SEARCH);
            answer_lower = global::fncs::to_lower(answer);
        }
    } while (invalid_answer(answer_lower));
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
        search::unzip_first_componets(movies_found);
    vector<string> movies_not_found =
        global::fncs::difference(movies, movies_title_found);

    output::movies_not_found(movies_not_found);
    output::separate();

    ask_if_another_file();
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