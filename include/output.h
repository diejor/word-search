/*
 * Diego R.R.
 * started: 09/28/2023
 * CS2337.501
 * functions used to handle output
 */

#ifndef OUTPUT_HANDLER_HPP
#define OUTPUT_HANDLER_HPP

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "global.h"
#include "search.h"

using namespace std;

/*
 * Outputs is defined as displaying to the terminal where the user interacts. See ppm_stream.h for the definition of outputting to a file.
 */
namespace output {
void separate() { cout << endl; }

void soup(vector<vector<char>> soup) {
    cout << "rows: " << soup.size() << " x "
         << "cols: " << soup[0].size() << endl;
    for (const vector<char> &row : soup) {
        for (char letter : row) {
            cout << letter << " ";
        }
        cout << endl;
    }
}

int max_movie_length(
    const vector<tuple<string, int, int, search::Direction>> &movies) {
    int max_length = 0;
    for (const tuple<string, int, int, search::Direction> &movie : movies) {
        string movie_title = search::get_title(movie);
        if (movie_title.length() > max_length) {
            max_length = movie_title.length();
        }
    }
    return max_length;
}

void format_result(int max_movie_len, const string &movie_title, const string &row,
                   const string &col, const string &direction) {
    const int row_len = 10;
    const int col_len = 10;
    const int direction_len = 15;

    cout << left << setw(max_movie_len) << movie_title << left << setw(row_len)
         << row << left << setw(col_len) << col << left << setw(direction_len)
         << direction << endl;
}

/*
    See documentation of search::movies_in_soup function for more details of the
   movies parameter type.
*/
void movies_found(
    const vector<tuple<string, int, int, search::Direction>> &movies) {
    int max_movie_len = max_movie_length(movies) + 2;
    format_result(max_movie_len, "Movies Found", "Row", "Column", "Direction");
    for (tuple<string, int, int, search::Direction> movie : movies) {
        string movie_title = get<0>(movie);
        int row = search::get_row(movie);
        int col = search::get_col(movie);
        search::Direction direction = search::get_direction(movie);
        string direction_str = search::str_of_direction(direction);

        format_result(max_movie_len, movie_title, to_string(row + 1),
                      to_string(col + 1), direction_str);
    }
}

void movies_not_found(const vector<string> &movies_not_found) {
    cout << "Movies not found:" << endl;
    for (const string &movie : movies_not_found) {
        cout << movie << endl;
    }
}

void soup_field(const vector<vector<double>> &soup_field) {
    cout << "Soup Field:" << endl;
    for (const vector<double> &row : soup_field) {
        for (double num : row) {
            cout << setw(3) << num << " ";
        }
        cout << endl;
    }
}

void say_goodbye() { cout << global::msgs::GOODBYE << endl; }
}  // namespace output

#endif  // OUTPUT_HANDLER_HPP