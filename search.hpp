/*
    * search.hpp
    * Diego R.R.
    * started: 09/30/2023
    * CS2337.501
    * functions used to search movie titles in a soup of letters
    * changelog:
        - 09/30/2023 - header file created
*/

#ifndef MOVIE_SEARCHER_HPP
#define MOVIE_SEARCHER_HPP

#include <string>
#include <vector>

#include "global.hpp"

using namespace std;
using namespace global;

/*
    The term location is used to refer a pair of coordinates (row, col) in the soup of letters.
*/
namespace search {

    const string NOT_FOUND = "not found";

    /*
        Notice that the array of directions is clockwise started from south. and first component is the row and the second component is the column.
    */
    const vector<vector<int>> directions = {
        {1, 0},     // south
        {1, 1},     // south-east
        {0, 1},     // east
        {-1, 1},    // north-east
        {-1, 0},    // north
        {-1, -1},   // north-west
        {0, -1},    // west
        {1, -1}    // south-west
    };

    /*
        Used along with directions vector to get the direction of the next letter to search in the soup of letters.
    */
    enum Direction {
        SOUTH,
        SOUTH_EAST,
        EAST,
        NORTH_EAST,
        NORTH,
        NORTH_WEST,
        WEST,
        SOUTH_WEST,
        NONE
    };

    const Direction directions_ary[] = {
        Direction::SOUTH,
        Direction::SOUTH_EAST,
        Direction::EAST,
        Direction::NORTH_EAST,
        Direction::NORTH,
        Direction::NORTH_WEST,
        Direction::WEST,
        Direction::SOUTH_WEST
    };

    vector<int> vector_direction_of(Direction direction) {
        vector<int> dir = {0, 0};
        if (direction != Direction::NONE) {
            dir = directions[direction];
        }
        return dir;
    }

    bool compare_directions(Direction enum_dir1, Direction enum_dir2) {
        vector<int> vector_dir1 = vector_direction_of(enum_dir1);
        vector<int> vector_dir2 = vector_direction_of(enum_dir2);
        return vector_dir1 == vector_dir2;
    }

    bool compare_directions(vector<int> dir1, vector<int> dir2) {
        return dir1[0] == dir2[0] && dir1[1] == dir2[1];
    }

    bool compare_directions(vector<int> vector_dir, Direction enum_dir) {
        return compare_directions(vector_dir, vector_direction_of(enum_dir));
    }

    bool compare_directions(Direction enum_dir, vector<int> vector_dir) {
        return compare_directions(vector_dir, enum_dir);
    }
    
    Direction enum_direction_of(vector<int> dir) {
        Direction direction = Direction::NONE;
        for (Direction dir_compare : directions_ary) {
            if (compare_directions(dir, dir_compare)) {
                direction = dir_compare;
                break;
            }
        }
        return direction;
    }

    /*
        Helper function of is_in_range function.
    */
    bool within_rows(int row, int num_rows) {
        return row >= 0 && row < num_rows;
    }

    /*
        Helper function of is_in_range function.
    */
    bool within_cols(int col, int num_cols) {
        return col >= 0 && col < num_cols;
    }

    /*
        Used to check wether the direction where the location was moved is within the range of the soup of letters.
    */
    bool in_range(int row, int col, int num_rows, int num_cols) {
        return within_rows(row, num_rows) && within_cols(col, num_cols);
    }

    string str_of_dir(Direction dir) {
        string dir_str = "NONE";
        switch (dir) {
            case Direction::SOUTH:
                dir_str = "South";
                break;
            case Direction::SOUTH_EAST:
                dir_str = "South-East";
                break;
            case Direction::EAST:
                dir_str = "East";
                break;
            case Direction::NORTH_EAST:
                dir_str = "North-East";
                break;
            case Direction::NORTH:
                dir_str = "North";
                break;
            case Direction::NORTH_WEST:
                dir_str = "North-West";
                break;
            case Direction::WEST:
                dir_str = "West";
                break;
            case Direction::SOUTH_WEST:
                dir_str = "South-West";
                break;
            default:
                break;
        }
        return dir_str;
    }

    /*
        Used to build the string that contains the information of the location and direction where the movie title was found in the soup of letters. 
        
        The string is passed to the collector of movie titles found, if the string is equal to NOT_FOUND, the movie title was not found in the soup of letters. Otherwise, the movie title was found and the information to find it in the soup is encoded in the returned string as: str = "row col direction".
    */
    string build_loc_and_dir_result(int row, int col, Direction direction) {
        return "row:"+to_string(row) + " " + "col:"+to_string(col) + " " + str_of_dir(direction);
    }

    bool match(vector<vector<char>> soup, int row, int col, char movie_letter) {
        bool in_boundaries = in_range(row, col, soup.size(), soup[0].size());
        char soup_letter = soup[row][col];
        return in_boundaries && soup_letter == movie_letter;
    }

    bool is_movie_in_direction(vector<vector<char>> soup, string movie_title, int row, int col, Direction direction_to_check) {
        bool in_dir = false; // assume is not in given direction
        for (int movie_str_idx = 0; movie_str_idx < movie_title.size(); movie_str_idx++) {
            char movie_letter = movie_title[movie_str_idx];
            int row_dir = vector_direction_of(direction_to_check)[0];
            int col_dir = vector_direction_of(direction_to_check)[1];
            int row_to_check = row + row_dir * movie_str_idx;
            int col_to_check = col + col_dir * movie_str_idx;
            if (match(soup, row_to_check, col_to_check, movie_letter)) {
                in_dir = true; // proved wrong
            }
        }
        return in_dir;
    }

    Direction is_movie_in_location(vector<vector<char>> soup, string movie_title, int row, int col) {
        // debug::flow_control(__func__);
        Direction dir_result = Direction::NONE; // assume is not in soup
        for (Direction dir : directions_ary) {
            if (is_movie_in_direction(soup, movie_title, row, col, dir)) {
                dir_result = dir; // proved wrong
            }
        }
        return dir_result;
    }

    string format_movie_title(string movie_title) {
        string formatted = "";
        for (char letter : movie_title) {
            if (!isalpha(letter)) {
                formatted += toupper(letter);
            }
        }
        debug::movie_title_formatted(movie_title, formatted);
        return formatted;
    }

    string is_movie_title_in_soup(vector<vector<char>> soup, string movie_title) {
        debug::flow_control(__func__);
        string result = NOT_FOUND;
        int num_cols = soup[0].size();
        string formatted = format_movie_title(movie_title);
        for (int row = 0; row < soup.size(); row++) {
            for (int col = 0; col < soup[0].size(); col++) {
                Direction dir = is_movie_in_location(soup, formatted, row, col);
                if (dir != Direction::NONE) {
                    string loc_and_dir = build_loc_and_dir_result(row, col, dir);
                    result = movie_title + " found in " + loc_and_dir;
                }
            }
        }
        return result;
    }

    vector<string> movie_title_searcher(vector<vector<char>> soup, vector<string> movie_titles) {
        debug::flow_control(__func__);
        vector<string> movie_titles_found;
        for (string movie_title : movie_titles) {
            string result = is_movie_title_in_soup(soup, movie_title);
            debug::movie_title_result(result, NOT_FOUND);
            if (result != NOT_FOUND) {
                movie_titles_found.push_back(result);
            }
        }
        return movie_titles_found;
    }

}

#endif // MOVIE_SEARCHER_HPP