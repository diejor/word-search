//
// Created by diejo on 10/7/2023.
//

#ifndef SOUP_FIELD_H
#define SOUP_FIELD_H

#include <cmath>
#include <string>
#include <tuple>
#include <vector>

#include "global.h"
#include "ppm_stream.h"
#include "search.h"

using namespace std;
using namespace global::fncs;

/*
 * A field is no more than a 2D matrix of doubles that represents the strength of the field at each position in the soup of letters. The field is based on the "mass" of each letter given by LETTER_MASS constant and the FIELD_CONST.
 * Fields are important for the program because they define how heat maps are created which are the standard ppm output of the program.
 */
namespace fields {
const double FIELD_CONST = 1;
const double LETTER_MASS = 1;

/*
 * NORMAL polarization allows both directions to contribute to the field whereas COMPLETE polarization only allows one direction. NONE for no polarization at all, which just adds the field of the letters.
 *
 * Note that NONE polarization produces a red screen with word-searches that are filled with occurrences of movie titles.
 */
enum Polarization {
    NORMAL,
    COMPLETE,
    NONE
};

const string POLARIZATION_STRINGS[] = {
    "normal",
    "complete",
    "none"};

double dist_square(pair<int, int> p1, pair<int, int> p2) {
    int row_dist = p1.first - p2.first;
    int col_dist = p1.second - p2.second;
    return row_dist * row_dist + col_dist * col_dist;
}

double strength_of_field(double dist_square) {
    double weigth = LETTER_MASS * FIELD_CONST;
    if (dist_square == 0)
        return weigth;
    return weigth / (dist_square);
}

/*
 * Uses the LETTER_MASS constant to determine how much of the strong the field is at a particular location. Essentially, the function is applying Newton's force of gravity equation to each position in the soup of letters to initialize the strength of the field. Notice that the strength decays to the square of the distance between the letter and the position. Polarization is considered by multiplying the normalized direction of the movie title with the direction of the search dot product with the desired direction of polarization.
 *
 */
void place_letter(
    vector<vector<double>> &soup_field,
    pair<int, int> let_loc,
    double polarization) {
    int rows = soup_field.size();
    int cols = soup_field[0].size();

    if (polarization == 0)
        return;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            pair<int, int> curr_loc = make_pair(row, col);
            double curr_dist_square = dist_square(curr_loc, let_loc);
            soup_field[row][col] += strength_of_field(curr_dist_square) * polarization;
        }
    }
}

bool close_enough(double num1, double num2) {
    return abs(num1 - num2) < 0.0001;
}

/*
 * The polarization factor is the multiplier used with strength_of_field to determine how much of the field is contributed by the movie title considering the polarization of the movie title when it was found with a particular direction.
 */
double polarization_factor(search::Direction polarization, pair<int, int> dir, Polarization polarization_type) {
    pair<int, int> pol_vec = search::pair_of(polarization);
    double polarization_factor = dmath::fncs::how_much_in_dir(pol_vec, dir);
    switch (polarization_type) {
        case NORMAL:
            polarization_factor = abs(polarization_factor);
            break;
        case COMPLETE:
            if (!close_enough(polarization_factor, 1))
                polarization_factor = 0;
            break;
        default:
            polarization_factor = 1;
            break;
    }
    return polarization_factor;
}

/*
 * First abstraction of field creation. Handles the placement of the movie title in the soup of letters and do not consider how much weight each movie contributes, this is done by place_letter.
 * Basically an intermediary function between place_letter and universal.
 */
void place_movie(vector<vector<double>> &soup_field,
                 const string &title_formatted,
                 int row, int col,
                 pair<int, int> dir,
                 search::Direction polarization,
                 Polarization polarization_type) {
    int row_dir = get_row(dir);
    int col_dir = get_col(dir);
    double pol_factor = polarization_factor(polarization, dir, polarization_type);

    for (int let_idx = 0; let_idx < title_formatted.size(); let_idx++) {
        int let_row = row + let_idx * row_dir;
        int let_col = col + let_idx * col_dir;
        pair<int, int> let_loc = make_pair(let_row, let_col);
        place_letter(soup_field, let_loc, pol_factor);
    }
}

/*
 * Initializes a fresh soup field with all zeros with the dimensions of the soup of letters.
 */
vector<vector<double>> init_field(const unsigned int rows, const unsigned int cols) {
    vector<vector<double>> soup_field(rows, vector<double>(cols, 0));
    return soup_field;
}

/*
 * Universal soup field refers to the field that each movie title creates in the soup of letters. Similar to gravitational fields, letters of each movie titles are thought to have "mass" that contribute to the field. The polarization due the direction of search of the movie title is also considered when creating the field.
 *
 * It will be used to create heat maps of the soup of letters, witch are later translated to ppm files.
 */
vector<vector<double>> universal(
    const vector<vector<char>> &soup,
    const vector<tuple<string, int, int, search::Direction>> &movies_found,
    search::Direction polarization,
    Polarization polarization_type) {
    unsigned int rows = soup.size();
    unsigned int cols = soup[0].size();
    vector<vector<double>> soup_field = init_field(rows, cols);

    for (const tuple<string, int, int, search::Direction> &movie : movies_found) {
        string title = search::get_title(movie);
        string title_formatted = global::fncs::format_string(title);

        int row = search::get_row(movie);
        int col = search::get_col(movie);
        search::Direction dir = search::get_direction(movie);
        pair<int, int> dir_pair = search::pair_of(dir);

        place_movie(soup_field, title_formatted, row, col, dir_pair, polarization, polarization_type);
    }

    return soup_field;
}
}  // namespace fields

#endif  // SOUP_FIELD_H
