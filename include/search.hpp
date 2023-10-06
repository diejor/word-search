/*
    * search.hpp
    * Diego R.R.
    * started: 09/30/2023
    * CS2337.501
    * functions used to search movie titles in a soup of letters
    * changelog:
        - 09/30/2023 - header file created
*/

#include <string>
#include <tuple>
#include <vector>

using namespace std;

#ifndef MOVIE_SEARCHER_HPP
#define MOVIE_SEARCHER_HPP

/*
    Movies found are handled as a tuple<string, tuple<int,int,Direction>>. The
   first component of the tuple is the movie title, the second component is the
   result of the search. The result of the search is a tuple<int,int,Direction>
   where the first component is the row where the movie title was found, the
   second component is the column where the movie title was found and the third
   component is the direction where the movie title was found.
*/
namespace search {

// =----------------- Spatial abstraction -----------------=

/*
    Used along with directions_components vector to get the direction of the
   next letter to search in the soup of letters.
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

const Direction DIRECTIONS_ARY[] = {Direction::SOUTH, Direction::SOUTH_EAST,
                                    Direction::EAST, Direction::NORTH_EAST,
                                    Direction::NORTH, Direction::NORTH_WEST,
                                    Direction::WEST, Direction::SOUTH_WEST};

/*
    Notice that the directions are anti-clockwise started from south. The first
   component is the row and the second component is the column.
*/
const pair<int, int> DIRECTION_COMPONENTS[8] = {
    {1, 0},    // south
    {1, 1},    // south-east
    {0, 1},    // east
    {-1, 1},   // north-east
    {-1, 0},   // north
    {-1, -1},  // north-west
    {0, -1},   // west
    {1, -1}    // south-west
};

// =----------------- End of spatial abstraction -----------------=

/*
    Used to indicate that the movie title was not found in the soup of letters
   search algorithm.
*/
const tuple<string, int, int, Direction> NOT_FOUND = {"", -1, -1, Direction::NONE};

// ------------------------------------------------------
// =----------------- PUBLIC INTERFACE -----------------=
string str_of_direction(Direction direction);

string get_title(tuple<string, int, int, Direction> search_result);
int get_row(tuple<string, int, int, Direction> search_result);
int get_col(tuple<string, int, int, Direction> search_result);
Direction get_direction(tuple<string, int, int, Direction> search_result);


vector<tuple<string, int, int, Direction>> movies_in_soup(vector<vector<char>> soup, vector<string> movies);

vector<string> unzip_first_componets(vector<tuple<string, int, int, Direction>> movies_found);
// =----------------- END OF PUBLIC INTERFACE ----------=

}  // namespace search

namespace search::debug {
void movie_title_formatted(string movie_title, string movie_title_formatted);
void search_loc_step(int row, int col, string movie);
void search_dir_step(string direction, string movie);
void movie_found(string movie, int row, int col, string direction);
void movie_not_found(string movie_title);
}




#endif  // MOVIE_SEARCHER_HPP