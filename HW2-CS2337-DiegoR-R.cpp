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
    Notes:
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "modules/debug.hpp"
#include "modules/global.hpp"
#include "modules/input_loader.hpp"
#include "modules/parser.hpp"
#include "modules/output_handler.hpp"
#include "modules/error.hpp"

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

vector<string> movie_title_searcher(vector<vector<char>> soup_of_letters, vector<string> movie_titles_to_search) {
    return vector<string>();
}

void run_program() {
    ifstream input_file = input_loader::get_input_file();

    vector<vector<char>> soup_of_letters = parser::soup_letter(input_file);
    vector<string> movie_titles_to_search = parser::movie_titles_to_search(input_file);

    vector<string> movie_titles_found = movie_title_searcher(soup_of_letters, movie_titles_to_search);
    vector<string> movie_titles_not_found = global::difference(movie_titles_to_search, movie_titles_found);
    output_handler::show_results(movie_titles_found, movie_titles_not_found);
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