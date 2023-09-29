/*
    * parser.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to parse input file
    * changelog:
        - 09/29/2023 - header file created
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <fstream>

using namespace std;

namespace parser {

    vector<vector<char>> soup_letter(ifstream &input_file) { 
        return vector<vector<char>> {}; 
    }

    /// @brief Parses the input file and returns a vector of strings that represents the movie titles to search. Note that the input file is already open and is soup of letters is assumed to be already parsed.
    /// @param soup_of_letters A 2D array of characters that represents the soup of
    /// letters
    /// @param movie_titles_to_search A vector of strings that represents the movie
    /// titles to search
    /// @return A vector of strings that represents the movie titles found in the
    /// soup of letters
    vector<string> movie_titles_to_search(ifstream &input_file) {
        return vector<string>();
    }
}

#endif // PARSER_HPP
