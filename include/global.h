/*
    * global.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * global functions used in word search program
    * changelog:
        - 09/28/2023 - header files created
*/

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <string>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

// =---------   GLOBAL DEFINITIONS   ---------=
namespace global {
    // =-------------- MESSAGES ---------------=
    namespace msgs {
        const string WELCOME = "Welcome to the Movie Title Searcher!";

        // input
        const string ENTER_FILE_NAME = "* enter file name: ";
        const string ENTER_FILE_NAME_AGAIN = "* enter file name again: ";
        const string USING_FILE = "* using file: ";

        // error
        const string INVALID_EXTENSION = "Invalid file extension. Enter one of the following extensions: ";
        const string PROGRAM_FAILED = "The program got the following error: ";

        const string ANOTHER_SEARCH = "Do you want to search for another movie title? (yes/no): ";
        const string INVALID_ANSWER = "Sorry I couldn't understand your answer.";
        const string GOODBYE = "Thank you for using this word-search program!";
    }

    void show_msg_noline(string msg) {
        cout << msg;
    }

    void show_msg_noline(string msg, string msg2) {
        cout << msg << msg2;
    }

    void show_msg(string msg) {
        cout << msg << endl;
    }

    void show_msg(string msg, string msg2) {
        cout << msg << msg2 << endl;
    }

    void show_msg_dobleline(string msg) {
        cout << msg << endl << endl;
    }

    void show_msg_dobleline(string msg, string msg2) {
        cout << msg << msg2 << endl << endl;
    }

    string format_result(int row, int col, string direction) {
        return "row:" + to_string(row+1) + ", col:" + to_string(col+1) + " along " + direction;
    }
    // =------------ END OF MESSAGES ------------=



    // =--------------- EXTENSIONS DEFINITIONS ---------------=
    namespace valid_extensions {

        /// @brief Valid extensions for the input file.
        const string EXTENSIONS[] = {
            "txt"
        };

        /// @brief Checks if the input file name has the extension provided.
        bool has(string input_file_name, string extension) {
            return input_file_name.substr(input_file_name.find_last_of(".") + 1) ==
                extension;
        }

        /// @brief Checks if the input file name has a valid extension.
        bool has(string intput_file_name) {
            bool has_valid_extension = false;
            for (string extension : EXTENSIONS) {
                if (has(intput_file_name, extension)) {
                    has_valid_extension = true;
                    break;
                }
            }
            return has_valid_extension;
        }
    } // end namespace valid_extensions
    // =--------------- EXTENSIONS DEFINITIONS ---------------=



    // =----------------- DEBUG DEFINITIONS ----------------------=
    namespace debug {

        // debug flags, if true the program will show debug messages
        namespace flags {
            const bool CONTROL_FLOW = true;

            // global functions
            const bool ADDING_TO_DIFFERENCE = false;

            // input loader flags
            const bool USER_INPUT = false; 
            const bool TRY_OPEN_FILE = false;
            const bool TRIM_WHITESPACE = false;

            // parser flags
            const bool EMPTY_FILE = false;
            const bool TOKEN_LINE = false;
            const bool IGNORING_COMMENT_LINE = false;
            const bool SOUP_OF_LETTERS_DIM = false;
            const bool SOUP_OF_LETTERS = false;
            const bool MOVIE_TITLES_TO_SEARCH = false;

            // word searcher flags
            const bool MOVIE_TITLE_FORMATTED = false;
            const bool MOVIE_TITLE_FOUND = false;
            const bool MOVIE_TITLE_NOT_FOUND = false;
            const bool SEARCH_LOC_STATE = false;
            const bool SEARCH_DIR_STATE = false;
        }

        void control_flow(string function_str) {
            if (flags::CONTROL_FLOW) {
                show_msg("DEBUG: calling: ", function_str);
            }
        }

        void control_flow(string function_str, string msg) {
            if (flags::CONTROL_FLOW) {
                show_msg_noline("DEBUG: calling: ", function_str);
                show_msg(" with msg: ", msg);
            }
        }

        void control_flow(string function_str, char ch) {
            if (flags::CONTROL_FLOW) {
                show_msg_noline("DEBUG: calling: ", function_str);
                show_msg(" with char: ", string(1, ch));
            }
        }

        void user_input(string input_file_name) {
            if (flags::USER_INPUT) {
                show_msg("DEBUG: user input: ", input_file_name);
            }
        }

        void open_file(string input_file_name) {
            if (flags::TRY_OPEN_FILE) {
                show_msg("DEBUG: trying to open file: ", input_file_name);
            }
        }

        void trim_whitespace(string input_file_name, int first_whspace_idx, int last_whspace_idx, string trimmed_input_file_name) {
            if (flags::TRIM_WHITESPACE) {
                show_msg("DEBUG: trimming whitespace from: ", input_file_name);
                show_msg("DEBUG: first whitespace index: ", to_string(first_whspace_idx));
                show_msg("DEBUG: last whitespace index: ", to_string(last_whspace_idx));
                show_msg("DEBUG: trimmed input file name: ", trimmed_input_file_name);
            }
        }

        void is_file_empty(bool is_empty) {
            if (flags::EMPTY_FILE) {
                show_msg("DEBUG: is file empty: ", is_empty ? "true" : "false");
            }
        }

        void ignoring_line(string line) {
            if (flags::IGNORING_COMMENT_LINE) {
                show_msg("DEBUG: ignoring line: ", line);
            }
        }

        void token_line(string token_line) {
            if (flags::TOKEN_LINE) {
                show_msg("DEBUG: token line: ", token_line);
            }
        }

        void soup_of_letters_dim(int rows, int cols) {
            if (flags::SOUP_OF_LETTERS_DIM) {
                show_msg("DEBUG: soup of letters dimensions: ", to_string(rows) + "x" + to_string(cols));
            }
        }

        void soup_of_letters(vector<vector<char>> soup_of_letters) {
            if (flags::SOUP_OF_LETTERS) {
                show_msg("DEBUG: soup of letters: ");
                for (vector<char> line : soup_of_letters) {
                    for (char letter : line) {
                        cout << letter << " ";
                    }
                    cout << endl;
                }
            }
        }

        void movie_titles_to_search(vector<string> movie_titles_to_search) {
            if (flags::MOVIE_TITLES_TO_SEARCH) {
                show_msg("DEBUG: vector of movie titles to search: ");
                for (string movie : movie_titles_to_search) {
                    show_msg(movie);
                }
            }
        }

        void movie_title_formatted(string movie, string movie_title_formatted) {
            if (flags::MOVIE_TITLE_FORMATTED) {
                show_msg("DEBUG: movie movie: ", movie);
                show_msg("DEBUG: movie movie formatted: ", movie_title_formatted);
            }
        }

        void search_step(string movie) {
            show_msg_noline("DEBUG: searching for movie movie: ", movie);
        }


        void search_loc_step(int row, int col, string movie) {
            if (flags::SEARCH_LOC_STATE) {
                search_step(movie);
                show_msg(" at ", to_string(row) + ", " + to_string(col));
            }
        }

        void search_dir_step(string direction, string movie) {
            if (flags::SEARCH_DIR_STATE) {
                search_step(movie);
                show_msg(" along ", direction);
            }
        }

        void movie_found(string movie, int row, int col, string direction) {
            if (flags::MOVIE_TITLE_FOUND) {
                show_msg_noline("DEBUG: search result: ", movie);
                show_msg(" found at ", format_result(row, col, direction));
            }
        }

        void movie_not_found(string movie) {
            if (flags::MOVIE_TITLE_NOT_FOUND) {
                show_msg_noline("DEBUG: search result: ", movie);
                show_msg(" not found");
            }
        }

        void adding_to_difference(string movie) {
            if (flags::ADDING_TO_DIFFERENCE) {
                show_msg("DEBUG: adding to difference: ", movie);
            }
        }
    } // end namespace debug
    // =--------- END OF DEBUG DEFINITIONS ---------=



    // =----------------- ERROR HANDLING -----------------=
    namespace error {

        /*
            Called when input::get_file_name_validated() receives an invalid file extension from the user. Hence we have to show the user the valid extensions.
        */
        void file_extension() {
            show_msg(msgs::INVALID_EXTENSION, " ");
            // show possible valid extensions
            for (string valid_extension : valid_extensions::EXTENSIONS) {
                show_msg(valid_extension, " ");
            }
            cout << endl;
        }

        /*
            Called when input::try_open_file() fails to open the file because the file doesn't exists in the current directory.
        */
        void opening_file() {
            perror(msgs::PROGRAM_FAILED.c_str());
        }

        /*
            Called when parser::get_next_token_line() receives an empty file when it should have content (see more details of the error in the function documentation).
        */
        void empty_file() {
            show_msg("The file is empty when expected to have content.");
        }

        void not_tuple() {
            show_msg("The vector is not a tuple");
        }
    }
    // =--------------- END OF ERROR HANDLING ---------------=


    // =----------------- GLOBAL HELPER FUNCTIONS -----------------=

    /*
        Helper fuction of difference function.
    */
    bool is_str_in_vector(string str, vector<string> v) {
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
    vector<string> difference(vector<string> v1, vector<string> v2) {
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
    string trim_whitespace(string str) {
        int first = str.find_first_not_of(' ');
        int last = str.find_last_not_of(' ');
        string trimmed_str = str.substr(first, (last - first + 1));
        debug::trim_whitespace(str, first, last, trimmed_str);
        return trimmed_str;
    }

    string to_lower(string str) {
        string lower_case_str = "";
        for (char ch : str) {
            lower_case_str += tolower(ch);
        }
        return lower_case_str;
    }

    bool contains(string str, string regex) {
        return str.find(regex) != string::npos;
    }

    // =--------------- END OF HELPER FUNCTIONS ----------------=
}
// =--------- END OF GLOBAL DEFINITIONS ---------=

#endif // GLOBAL_HPP