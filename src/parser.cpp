

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "global.hpp"
#include "parser.hpp"

using namespace std;
using namespace parser;


const char NOT_TOKENS[] = {'#', '\n'};

bool is_comment_line(ifstream &input_file) { return input_file.peek() == '#'; }

bool is_empty_line(ifstream &input_file) { return input_file.peek() == '\n'; }

bool is_file_empty(ifstream &input_file) { return input_file.peek() == EOF; }

/*
    This function defines what is a token line which is any line that the first
   character doesn't contain any NOT_TOKENS char.

    This definition is important since when the internal pointer of the ifstream
   file is at EOF it is considered a token line (see consume_file function
   documentation for more details of it's impotance).
*/
bool is_token_line(ifstream &input_file) {
    char first_line_char = input_file.peek();
    bool is_token_line = true;  // assert the first char is not a NOT_TOKENS char
    for (char not_token :
         NOT_TOKENS) {  // check universally for all NOT_TOKENS chars
        is_token_line = is_token_line && (first_line_char != not_token);
    }
    return is_token_line;
}

/*
    This function is called to assert that the internal pointer of the ifstream
   file is not at the end of the file. Note that the end of the file is a token
   line (see is_token_line function).

    If it is the case that the pointer is at the end of the file and this
   functions was called, it means the program tried to read a non-empty token
   line (e.i the rows and columns dimensions line), but the file was empty. The
   program should recover at this point asking a new input file to the user.
   Since working this without having advance tools, such as the option<type>
   feature, its a nightmare in my opinion, I decided to just assume that the
   input file will always have the expected two blocks of tokens.
*/
void assert_non_empty_file(ifstream &input_file) {
    if (is_file_empty(input_file)) {
        error::empty_file();
    }
}

/*
    A helper function for get_next_token_line. All comment and empty lines that
   should be ignored by the parser are handled by this function.

    One result of the state of the ifstream file passed, the function always
   advances it's internal pointer to the next token line.
*/
void advance_to_token(ifstream &input_file) {
    string line;
    while (!is_token_line(input_file)) {
        getline(input_file, line);
        parser::debug::ignoring_line(line);
    }
}

/*
    This function is used for to read lines fom the blocks of tokens.

*/
string get_next_token_line(ifstream &input_file) {
    advance_to_token(input_file);
    string token_line;
    getline(input_file, token_line);
    parser::debug::token_line(token_line);
    return token_line;
}

/*
    This function is used to get the rows of the soup.
*/
vector<string> get_token_block(ifstream &input_file, unsigned int block_size) {
    vector<string> token_block;
    while (token_block.size() < block_size) {
        string token_line = get_next_token_line(input_file);
        token_block.push_back(token_line);
    }
    return token_block;
}

/*
    Because the parser read the rows of the soup of letters as strings
   representing a line of letters (e.i "ABDFAFWEA"), this function is needed to
   convert the soup of letters from the vector of letter strings to a vector of
   vectors of chars.

    Example:
        1. vector<string> soup_str =   {"ABDFAFWEA",
                                        "ABDFAFWEA",
                                        "ABDFAFWEA"};
        2. vector<vector<char>> soup_char =
            {{'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'},
            {'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'},
            {'A', 'B', 'D', 'F', 'A', 'F', 'W', 'E', 'A'}};

    This conversion is needed since the movie searcher algorithm uses a vector
   of vectors of chars to represent the soup of letters instead of a vector of
   strings.

    If an empty vector of strings is passed, an empty vector of vectors of chars
   should be returned.
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
    It's expected to be the first parser function called to read tokens from the
   input file. The function assumes that the first token line is the dimensions
   of the soup of letters and then reads the subsequent lines to form the soup
   of letters.
*/
vector<vector<char>> parser::soup_letters(ifstream &input_file) {
    string soup_dim_line = get_next_token_line(input_file);
    int num_rows = stoi(soup_dim_line);
    int num_cols = stoi(soup_dim_line);
    vector<string> soup_str = get_token_block(input_file, num_rows);
    vector<vector<char>> soup = soup_str_to_char(soup_str);
    debug::soup_of_letters(soup);
    debug::soup_of_letters_dim(num_rows, num_cols);
    return soup;
}

/*
    This function is used to read the movie titles to search tokens. Notice that
   is practically the same to get_token_block() but it doesn't have a block size
   parameter which means that the file will be consumed after this function is
   called.
*/
vector<string> consume_file(ifstream &input_file) {
    vector<string> token_block;
    while (!is_file_empty(input_file)) {
        string token_line = get_next_token_line(input_file);
        token_block.push_back(token_line);
    }
    parser::debug::is_empty_file(true);

    // The last token line is always an empty line. To see this read the
    // definition of a token line in is_token_line function. Consequently, when
    // an empty file is read, it returns an empty string which has to be
    // removed.
    if (token_block.size() > 0) {
        token_block.pop_back();
    }

    return token_block;
}

/*
    It is assumed that before this function is called, the soup block of tokens
   was already read from the input file.

    Basically a wrapper function of consume_file() to convey a clearer meaning
   of what consume_file() is used for.

    One concern to be aware of is that this function essentially consumes the
   rest of the input file.
*/
vector<string> parser::movies_to_search(ifstream &input_file) {
    vector<string> movie_titles_to_search = consume_file(input_file);
    return movie_titles_to_search;
}

// ----------------------------------------
// =--------------- DEBUG  ---------------=
void parser::debug::is_empty_file(bool is_empty) {
    if (global::debug_flags::EMPTY_FILE) {
        global::fncs::show_msg("DEBUG: is file empty: ", is_empty ? "true" : "false");
    }
}

void parser::debug::ignoring_line(string line) {
    if (global::debug_flags::IGNORING_COMMENT_LINE) {
        global::fncs::show_msg("DEBUG: ignoring line: ", line);
    }
}

void parser::debug::token_line(string token_line) {
    if (global::debug_flags::TOKEN_LINE) {
        global::fncs::show_msg("DEBUG: token line: ", token_line);
    }
}

void parser::debug::soup_of_letters_dim(int rows, int cols) {
    if (global::debug_flags::SOUP_OF_LETTERS_DIM) {
        global::fncs::show_msg("DEBUG: soup of letters dimensions: ",
                         to_string(rows) + "x" + to_string(cols));
    }
}

void parser::debug::soup_of_letters(vector<vector<char>> soup_of_letters) {
    if (global::debug_flags::SOUP_OF_LETTERS) {
        global::fncs::show_msg("DEBUG: soup of letters: ");
        for (vector<char> line : soup_of_letters) {
            for (char letter : line) {
                cout << letter << " ";
            }
            cout << endl;
        }
    }
}

void parser::debug::movies_to_search(vector<string> movie_titles_to_search) {
    if (global::debug_flags::MOVIE_TITLES_TO_SEARCH) {
        global::fncs::show_msg("DEBUG: vector of movie titles to search: ");
        for (string movie : movie_titles_to_search) {
            global::fncs::show_msg(movie);
        }
    }
}
// =------------- END OF DEBUG -------------=
// ------------------------------------------

// ------------------------------------------
// =--------------- ERROR  ---------------=
void parser::error::empty_file() {
    global::fncs::show_msg("ERROR: empty file");
    exit(1);
}