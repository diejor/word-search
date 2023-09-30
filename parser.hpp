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

#include "global.hpp"

using namespace std;

/*
    The parser always expects three blocks of tokens given an input file:
        1. The rows and columns dimensions line.
        2. The token block of soup of letters.
        3. The token block of movie titles to search.
*/
namespace parser {

    const char NOT_TOKEN[] = {'#', '\n'};

    bool is_comment_line(ifstream& input_file) {
        return input_file.peek() == '#';
    }

    bool is_empty_line(ifstream& input_file) {
        return input_file.peek() == '\n';
    }

    bool is_file_empty(ifstream& input_file) {
        return input_file.peek() == EOF;
    }

    /*
        This function defines what is a token line which is any line that doesn't contain any NOT_TOKEN char. 
        
        This definition is important since when the internal pointer of the ifstream file is at EOF it is considered a token line (see consume_file function documentation for more details of it's impotance).
    */
    bool is_token(ifstream& input_file) {
        bool is_token = true;
        for (char not_token : NOT_TOKEN) {
            is_token = is_token && (input_file.peek() != not_token);
        }
        return is_token;
    }

    /*
        This function is called to assert that the internal pointer of the ifstream file is not at the end of the file. 
        
        If it is the case that the pointer is at the end of the file, and this functions was called, it means the program tried to read an expected token line (e.i the rows and columns dimensions line) but the file was empty. The program should recover at this point asking a new input file to the user. Since working this without having advance tools, such as the option<type> feature of c++, its a nightmare in my opinion, I decided to just assume that the input file will always have the expected three blocks of tokens.
    */
    void assert_non_empty_file(ifstream& input_file) {
        if (is_file_empty(input_file)) {
            error::empty_file();
        }
    }

    /*
        A helper function for get_next_token_line. All comment and empty lines that should be ignored by the parser are handled by this function.
        
        One result of the state of the ifstream file passed, is that it always advances it's internal pointer to the next token line.

        Because the input file is assumed to always have three blocks of tokens, this function should never be called when the input file is empty or it doesn't containt the expected three blocks of tokens. In the case of these two scenarios, the program should recover asking a new input file to the user.
    */
    void advance_to_token(ifstream& input_file) {
        string line;
        while (!is_token(input_file)) {
            getline(input_file, line);
            global::debug::ignoring_line(line);
        }
    }

    /*
        This function is used for both to read the first token line of the input file (the rows and columns dimensions line) and to read the token lines of the soup of letters and movie titles to search.

        Notice that before calling advance_to_token(), the function asserts that the input file is not empty (see advance_to_token() documentation for more details of why).
    */
    string get_next_token_line(ifstream& input_file) {
        assert_non_empty_file(input_file);
        advance_to_token(input_file);
        string token_line;
        getline(input_file, token_line);
        global::debug::token_line(token_line);
        return token_line;
    }

    /*
        This function is used to read get the soup of letters token.
    */
    vector<string> get_token_block(ifstream& input_file, int block_size) {
        vector<string> token_block;
        while (token_block.size() < block_size) {
            string token_line = get_next_token_line(input_file);
            token_block.push_back(token_line);
        }
        return token_block;
    }

    /*
        This function is used to read the movie titles to search tokens. Notice that is practically the same to get_token_block() but it doesn't have a block size parameter which means that the file will be consumed after this function is called.
    */
    vector<string> consume_file(ifstream& input_file) {
        vector<string> token_block;
        while (!is_file_empty(input_file)) {
            string token_line = get_next_token_line(input_file);
            token_block.push_back(token_line);
        }
        debug::is_file_empty(true);

        // The last token line is always an empty line. To see this read the definition of a token line in is_token function. Consequently, when an empty file is read, it returns an empty string which has to be removed.
        if (token_block.size() > 0) {
            token_block.pop_back(); 
        }

        return token_block;
    }

    /*
        Because the parser read the rows of the soup of letters as strings representing a line of letters (e.i "ABDFAFWEA"), this function is needed to convert the soup of letters from the vector of letter strings to a vector of vectors of chars.

        Example:
            1. vector<string> soup_str =   {"ABDFAFWEA", 
                                            "ABDFAFWEA", 
                                            "ABDFAFWEA"};
            2. vector<vector<char>> soup_char = 
                {{'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'}, 
                {'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'}, 
                {'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'}};
        
        This conversion is needed since the movie searcher algorithm uses a vector of vectors of chars to represent the soup of letters instead of a vector of strings.

        If an empty vector of strings is passed, an empty vector of vectors of chars should be returned.
    */
    vector<vector<char>> soup_str_to_char(vector<string> soup_str) {
        vector<vector<char>> soup_char;
        for (string line : soup_str) {
            vector<char> line_char;
            for (char letter : line) {
                line_char.push_back(letter);
            }
            soup_char.push_back(line_char);
        }
        return soup_char;
    }

    /*
        This function reads the first two blocks of tokens from the input file:
            1. the rows and columns dimensions line.
            2. the token block of soup of letters.
        It's expected to be the first parser function called to read tokens from the input file.
    */
    vector<vector<char>> soup_letter(ifstream &input_file) { 
        string soup_dim_line = get_next_token_line(input_file);
        int num_rows = stoi(soup_dim_line);
        vector<string> soup_str = get_token_block(input_file, num_rows);
        vector<vector<char>> soup = soup_str_to_char(soup_str);
        return soup;
    }

    /*
        It is assumed that before this function is called, the other two blocks of tokens have been read from the input file:
            1. the rows and columns dimensions line.
            2. the token block of  soup of letters.
        
        Basically a wrapper function for consume_file() to convey a clearer meaning of what consume_file() is used for.
        
        One concern to be aware of is that this function essentially consumes the rest of the input file.
    */
    vector<string> movie_titles_to_search(ifstream &input_file) {
        vector<string> movie_titles_to_search = consume_file(input_file);
        return movie_titles_to_search;
    }
}

#endif // PARSER_HPP
