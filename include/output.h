/*
 * Diego R.R.
 * started: 09/28/2023
 * CS2337.501
 * functions used to handle output
 */

#ifndef OUTPUT_HANDLER_HPP
#define OUTPUT_HANDLER_HPP

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


#include "global.h"
#include "search.h"

using namespace std;

namespace output {
void separate() { cout << endl; }

void soup(vector<vector<char>> soup) {
    cout << "rows: " << soup.size() << " x "
         << "cols: " << soup[0].size() << endl;
    for (vector<char> row : soup) {
        for (char letter : row) {
            cout << letter << " ";
        }
        cout << endl;
    }
}

int max_movie_length(
    vector<tuple<string, tuple<int, int, search::Direction>>> movies) {
    int max_length = 0;
    for (tuple<string, tuple<int, int, search::Direction>> movie : movies) {
        string movie_title = get<0>(movie);
        if (movie_title.length() > max_length) {
            max_length = movie_title.length();
        }
    }
    return max_length;
}

void format_result(int max_movie_len, string movie_title, string row,
                   string col, string direction) {
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
    vector<tuple<string, tuple<int, int, search::Direction>>> movies) {
    int max_movie_len = max_movie_length(movies) + 2;
    format_result(max_movie_len, "Movies Found", "Row", "Column", "Direction");
    for (tuple<string, tuple<int, int, search::Direction>> movie : movies) {
        string movie_title = get<0>(movie);
        tuple<int, int, search::Direction> search_result = get<1>(movie);
        int row = search::get_row(search_result);
        int col = search::get_col(search_result);
        search::Direction direction = search::get_direction(search_result);
        string direction_str = search::str_of_direction(direction);

        format_result(max_movie_len, movie_title, to_string(row + 1),
                      to_string(col + 1), direction_str);
    }
}

void movies_not_found(vector<string> movies_not_found) {
    cout << "Movies not found:" << endl;
    for (string movie : movies_not_found) {
        cout << movie << endl;
    }
}

void say_goodbye() { cout << global::msgs::GOODBYE << endl; }
} // namespace output

#endif // OUTPUT_HANDLER_HPP