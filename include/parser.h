/*
    * parser.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to parse input file
    * changelog:
        - 09/29/2023 - header file created
        - 09/01/2023 - parser documentation improved
*/


#include <fstream>
#include <string>

using namespace std;

#ifndef PARSER_HPP
#define PARSER_HPP

/*
    The parser reads token liens from the input file. A token line is defined as
   a line of characters that satisfy the is_token_line function. Token liens are
   then grouped into blocks of tokens. A block of tokens is defined as a
   successive group of token lines. The parser expects two blocks of tokens from
   the input file:
        1. The token block of the soup. The first line consists of the
   dimensions (rows cols), the rows determine how many subsequent lines will be
   read to form the soup of letters.
        2. The token block of movie titles to search which is of an arbitrary
   size and should consume the rest of the input file when read.
*/
namespace parser {
    vector<vector<char>> soup_letters(ifstream &input_file);
    vector<string> movies_to_search(ifstream &input_file);
}

namespace parser::debug {
    void is_empty_file(bool is_empty);
    void ignoring_line(string line);
    void token_line(string token_line);
    void soup_of_letters_dim(int num_rows, int num_cols);
    void soup_of_letters(vector<vector<char>> soup);
    void movies_to_search(vector<string> movies);
}

namespace parser::error {
    void empty_file();
}

#endif // PARSER_HPP
