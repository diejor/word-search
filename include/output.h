/*
 * Diego R.R.
 * started: 09/28/2023
 * CS2337.501
 * functions used to handle output
 */


#include <vector>

#include "search.h"

#ifndef OUTPUT_HANDLER_HPP
#define OUTPUT_HANDLER_HPP

namespace output {
    void separate();
    void soup(vector<vector<char>> soup);
    void movies_found(const vector<tuple<string, int,int,search::Direction>>& movies);
    void movies_not_found(const vector<string>& movies);
    void soup_field(const vector<vector<int>>& soup_field);
    void say_goodbye();
}

#endif // OUTPUT_HANDLER_HPP