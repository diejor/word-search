//
// Created by diejo on 10/7/2023.
//


#include <string>
#include <tuple>
#include <vector>

#include "global.h"
#include "soup_field.h"
#include "search.h"


using namespace std;
using namespace global::fncs;

unsigned int dist(pair<int, int> p1, pair<int, int> p2) {
    unsigned int x = abs(get_row(p1) - get_row(p2));
    unsigned int y = abs(get_col(p1) - get_col(p2));
    return max(x, y);
}

unsigned int range(unsigned int rows, unsigned int cols, pair<int, int> loc) {
    int row = get_row(loc);
    int col = get_col(loc);
    int max_row = rows - 1;
    int max_col = cols - 1;
    int min_row = 0;
    int min_col = 0;

    int const row_dist = max(row - min_row, max_row - row);
    int const col_dist = max(col - min_col, max_col - col);

    return max(row_dist, col_dist);
}

void place_letter(vector<vector<int>> &soup_field, pair<int, int> let_loc, bool existential) {
    if (existential) {
        soup_field[get_row(let_loc)][get_col(let_loc)] += 1;
        return;
    }

    unsigned int rows = soup_field.size();
    unsigned int cols = soup_field[0].size();
    unsigned int furthest_dist = range(rows, cols, let_loc);
    int start_of_field = furthest_dist / 2;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            pair<int, int> curr_loc = make_pair(row, col);
            unsigned int curr_dist = dist(curr_loc, let_loc);
            soup_field[row][col] += start_of_field - curr_dist + 1;
        }
    }
}

void place_movie(vector<vector<int>> &soup_field, const string &title_formatted, int row, int col, pair<int, int> dir,
                 bool existential) {
    for (int let_idx = 0; let_idx < title_formatted.size(); let_idx++) {
        int let_row = row + let_idx * get_row(dir);
        int let_col = col + let_idx * get_col(dir);
        pair<int, int> let_loc = make_pair(let_row, let_col);
        place_letter(soup_field, let_loc, existential);
    }
}

vector<vector<int>> init_field(const unsigned int rows, const unsigned int cols) {
    vector<vector<int>> soup_field(rows, vector<int>(cols, 0));
    return soup_field;
}

/*
    The soup field is a matrix of integers that represents the graviotational field of the soup. It is used to then multiply the field by the weight of the letters which will be used to determinate the density of the soup. Used to create heat maps of the soup.
*/
vector<vector<int>> soup_field::universal(
        const vector<vector<char>> &soup,
        const vector<tuple<string, int, int, search::Direction>> &movies_found, bool existential) {
    unsigned int rows = soup.size();
    unsigned int cols = soup[0].size();
    vector<vector<int>> soup_field = init_field(rows, cols);

    for (const tuple<string, int, int, search::Direction> &movie: movies_found) {
        string title = search::get_title(movie);
        string title_formatted = global::fncs::format_string(title);

        int row = search::get_row(movie);
        int col = search::get_col(movie);
        search::Direction dir = search::get_direction(movie);
        pair<int, int> dir_pair = search::pair_of(dir);

        place_movie(soup_field, title_formatted, row, col, dir_pair, existential);
    }

    return soup_field;
}

vector<vector<int>> soup_field::existential(
        const vector<vector<char>> &soup,
        const vector<tuple<string, int, int, search::Direction>> &movies_found) {
    return universal(soup, movies_found, true);
}
