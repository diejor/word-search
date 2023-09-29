/*
    * error.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * 
    * functions used to handle errors
    * 
    * changelog:
        - 09/29/2023 - header file created
*/

#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

#include "global.hpp"
#include "debug.hpp"
#include "input_loader.hpp"
#include "valid_extensions.hpp"

using namespace std;

/// @brief Handling error module. Errors are comprehended as expected errors and failure errors. Failure errors are normally when the program creates a perror (e.i. when the program fails to open a file) such errors are possible to recover from and the program can continue to run. Expected errors are errors that are expected to happen and the program can recover more easily. For example, if the user enters an invalid file extension, the program can ask the user to enter the file name again.
namespace error {

    namespace msgs {
        const string INVALID_EXTENSION = "Invalid file extension. Enter one of the following extensions: ";
        const string PROGRAM_FAILED = "The program got the following error: ";
    }

    void file_extension(string input_file_name) {
        global::show_msg(msgs::INVALID_EXTENSION, " ");
        // show possible valid extensions
        for (string valid_extension : valid_extensions::EXTENSIONS) {
            global::show_msg(valid_extension, " ");
        }
        cout << endl;
    }

    void failed_opening_file(string input_file_name) {
        perror(msgs::PROGRAM_FAILED.c_str());
    }
}

#endif // ERROR_HPP