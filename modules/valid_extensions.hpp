/*
    * valid_extensions.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to validate file extensions
    * changelog:
        - 09/29/2023 - header file created
*/

#ifndef VALID_EXTENSIONS_HPP
#define VALID_EXTENSIONS_HPP

#include <string>

using namespace std;

namespace valid_extensions {
    const string EXTENSIONS[] = {
        "txt"
    };

    bool has(string input_file_name, string extension) {
        return input_file_name.substr(input_file_name.find_last_of(".") + 1) ==
            extension;
    }

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
} // namespace extensions

#endif // VALID_EXTENSIONS_HPP