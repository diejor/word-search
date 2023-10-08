//
// Created by diejo on 10/7/2023.
//

#ifndef WORD_SEARCH_SOUP_FIELD_H
#define WORD_SEARCH_SOUP_FIELD_H

#include <vector>
#include <string>
#include <tuple>

#include "search.h"

namespace soup_field {
    vector<vector<int>> universal(
            const vector<vector<char>> &soup,
            const vector<tuple<string, int, int, search::Direction>>& movies,
            bool existential = false);
    vector<vector<int>> existential(
            const vector<vector<char>> &soup,
            const vector<tuple<string, int, int, search::Direction>>& movies);
}

#endif //WORD_SEARCH_SOUP_FIELD_H
