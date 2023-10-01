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
    Notes:
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "global.hpp"
#include "input.hpp"
#include "parser.hpp"
#include "search.hpp"
#include "output.hpp"

using namespace std;


// =---------- INIT APP ----------=

void welcome_user() {
    global::show_msg(global::msgs::WELCOME); 
}

void init_program() { 
    welcome_user(); 
}

// =---------- END OF INIT APP ----------=



// =---------- FINALIZE APP ----------=
void finalize_word_search() {
    cout << "Thank you for using the Movie Title Searcher!" << endl;
}
// =---------- END OF FINALIZE APP ----------=



// =---------- RUN PROGRAM ----------=


void run_program() {
    ifstream input_file = input::get_input_file();

    parser::assert_non_empty_file(input_file);
    vector<vector<char>> soup_of_letters = parser::soup_letter(input_file);
    parser::assert_non_empty_file(input_file); // assume that the file is not empty
    vector<string> movie_titles_to_search = parser::movie_titles_to_search(input_file);
    debug::movie_titles_to_search(movie_titles_to_search);

    vector<string> movie_titles_found = search::movie_title_searcher(soup_of_letters, movie_titles_to_search);
    vector<string> movie_titles_not_found = global::difference(movie_titles_to_search, movie_titles_found);
    output::show_results(movie_titles_found, movie_titles_not_found);
}

// =---------- END OF RUN PROGRAM ----------=

// =------------ BODY OF THE PROGRAM ------------=
int main() {
    init_program();
    run_program();
    finalize_word_search();
    return 0;
}
// =------------ END OF BODY ------------=