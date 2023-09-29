/*
    * output_handler.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to handle output
    * changelog:
        - 09/29/2023 - header file created
*/

#ifndef OUTPUT_HANDLER_HPP
#define OUTPUT_HANDLER_HPP

#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace output_handler {

    void show_results(vector<string> movie_titles_found, vector<string> movie_titles_not_found) {
        cout << "Movie titles found: " << endl;
        for (string movie_title_found : movie_titles_found) {
            cout << movie_title_found << endl;
        }
        cout << endl;
        cout << "Movie titles not found: " << endl;
        for (string movie_title_not_found : movie_titles_not_found) {
            cout << movie_title_not_found << endl;
        }
    }

}

#endif // OUTPUT_HANDLER_HPP