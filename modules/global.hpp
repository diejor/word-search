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

using namespace std;

// =---------   GLOBAL FUNCTIONS   ---------=
namespace global {

    namespace msgs {
        const string WELCOME = "Welcome to the Movie Title Searcher!";
    }

    void show_msg_noline(string msg) {
        cout << msg;
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

    /// @brief A function to check if a string listed in a vector.
    /// @return true if the string is in the vector, false otherwise
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

    /// @brief A function that returns the difference between two vectors of strings. It is used to find the movie titles that were not found.
    /// @param v1 the vector to be substracted from v2
    /// @param v2 the vector to substract v1 from
    /// @return the new vector of strings representing v1 - v2
    vector<string> difference(vector<string> v1, vector<string> v2) {
        vector<string> difference;
        for (string str_in_v1 : v1) {
            if (!is_str_in_vector(str_in_v1, v2)) {
                difference.push_back(str_in_v1);
            }
        }
        return difference;
    }
}
// =---------  END OF GLOBAL FUNCTIONS   ---------=

#endif // GLOBAL_HPP