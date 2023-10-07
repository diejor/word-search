
#include <string>
#include <tuple>
#include <vector>

#include "global.hpp"
#include "search.hpp"

using namespace std;
using namespace search;


// =----------------- Tuple helper functions -----------------=
vector<string> search::unzip_first_componets(
    vector<tuple<string, int, int, Direction>> movies_found) {
    vector<string> movie_titles;
    for (tuple<string, int, int, Direction> movie_result :
         movies_found) {
        movie_titles.push_back(get<0>(movie_result));
    }
    return movie_titles;
}
// =----------------- End of tuple helper functions -----------------=

// =----------------- GETTERS -----------------=
/*
    Used to get the components of the direction tuple.
*/
int get_row(pair<int, int> dir) { return get<0>(dir); }

int get_col(pair<int, int> dir) { return get<1>(dir); }

/*
    Used to get the components of the result tuple.
*/
string search::get_title(tuple<string, int, int, Direction> result) { return get<0>(result); }

int search::get_row(tuple<string, int, int, Direction> result) { return get<1>(result); }

int search::get_col(tuple<string, int, int, Direction> result) { return get<2>(result); }

Direction search::get_direction(tuple<string, int, int, Direction> result) { return get<3>(result); }

// =----------------- End of GETTERS -----------------=

// =--------------------------------------------------=
// =----------------- STR conversions ----------------=
string str_of_loc_pair(pair<int, int> loc) {
    return to_string(get<0>(loc)) + " " + to_string(get<1>(loc));
}

string str_of_result(tuple<string, int, int, search::Direction> result) {
    return str_of_loc_pair(pair<int, int>(get_row(result), get_col(result))) +
           " " + to_string(get<2>(result));
}

string search::str_of_direction(Direction dir) {
    string dir_str = "NONE";
    switch (dir) {
        case Direction::SOUTH:
            dir_str = "South";
            break;
        case Direction::SOUTH_EAST:
            dir_str = "South East";
            break;
        case Direction::EAST:
            dir_str = "Eeast";
            break;
        case Direction::NORTH_EAST:
            dir_str = "North East";
            break;
        case Direction::NORTH:
            dir_str = "North";
            break;
        case Direction::NORTH_WEST:
            dir_str = "North West";
            break;
        case Direction::WEST:
            dir_str = "West";
            break;
        case Direction::SOUTH_WEST:
            dir_str = "South West";
            break;
        default:
            break;
    }
    return dir_str;
}
// =----------------- End of STR conversions -----------------=
// =----------------------------------------------------------=

// =----------------- ENUM-TUPLE interations -----------------=
/*
    Function is_movie_in_direction uses this functon to get the direction
   components of the direction tuple.
*/
pair<int, int> pair_of(Direction direction) {
    pair<int, int> dir = {0, 0};
    if (direction != Direction::NONE) {
        dir = DIRECTION_COMPONENTS[direction];
    }
    return dir;
}

bool compare_directions(pair<int, int> dir1, pair<int, int> dir2) {
    int row_dir1 = get_row(dir1);
    int col_dir1 = get_col(dir1);
    int row_dir2 = get_row(dir2);
    int col_dir2 = get_col(dir2);
    
    return row_dir1 == row_dir2 && col_dir1 == col_dir2;
}

bool compare_directions(Direction enum_dir1, Direction enum_dir2) {
    pair<int, int> tuple_dir1 = pair_of(enum_dir1);
    pair<int, int> tuple_dir2 = pair_of(enum_dir2);
    return compare_directions(tuple_dir1, tuple_dir2);
}

bool compare_directions(pair<int, int> pair_dir, Direction enum_dir) {
    return compare_directions(pair_dir, pair_of(enum_dir));
}

bool compare_directions(Direction enum_dir, pair<int, int> pair_dir) {
    return compare_directions(pair_dir, enum_dir);
}

Direction enum_direction_of(pair<int, int> dir) {
    Direction direction = Direction::NONE;
    for (Direction dir_compare : DIRECTIONS_ARY) {
        if (compare_directions(dir, dir_compare)) {
            direction = dir_compare;
            break;
        }
    }
    return direction;
}

// =----------------- End of ENUM-TUPLE interations -----------------=


// =----------------- Spatial helper functions -----------------=
/*
    Helper function of is_in_range function.
*/
bool within_rows(int row, int num_rows) { return row >= 0 && row < num_rows; }

/*
    Helper function of is_in_range function.
*/
bool within_cols(int col, int num_cols) { return col >= 0 && col < num_cols; }

/*
    Used to check wether the direction where the location was moved is within
   the range of the soup of letters.
*/
bool in_range(int row, int col, int num_rows, int num_cols) {
    return within_rows(row, num_rows) && within_cols(col, num_cols);
}
// =----------------- End of spatial helper functions -----------------=

// =================================================================================
// =-------------------------------- SEARCH ALGORITHM
// -----------------------------=
/*
    Helper function of is_movie_in_direction function used to pattern match the
   movie title with the soup of letters.
*/
bool match(vector<vector<char>> soup, int row, int col, char movie_letter) {
    bool in_boundaries = in_range(row, col, soup.size(), soup[0].size());
    return in_boundaries && soup[row][col] == movie_letter;
}

/*
    Third layer of abstraction of the search algorithm. This function is used to
   check if the movie title is in the given direction.
*/
bool is_movie_in_direction(vector<vector<char>> soup, string movie_title,
                           int row, int col, Direction direction_to_check) {
    search::debug::search_dir_step(str_of_direction(direction_to_check), movie_title);
    pair<int, int> dir = pair_of(direction_to_check);
    int row_dir = get_row(dir);
    int col_dir = get_col(dir);

    bool in_dir = true;  // assume is at given direction
    for (unsigned int movie_str_idx = 0; movie_str_idx < movie_title.size();
         movie_str_idx++) {
        char movie_letter = movie_title[movie_str_idx];
        int row_to_check = row + row_dir * movie_str_idx;
        int col_to_check = col + col_dir * movie_str_idx;
        if (!match(soup, row_to_check, col_to_check, movie_letter)) {
            in_dir = false;  // proved wrong
            break;
        }
    }
    return in_dir;
}

/*
    Optimization function of search algorithm. If a movie is at given direction
   it should satisfy that the end point of the movie title is within the range
   of the soup of letters.
*/
bool is_possible_direction(Direction direction_to_check, int row, int col,
                           int num_rows, int num_cols, int movie_title_size) {
    pair<int, int> dir = pair_of(direction_to_check);
    int row_dir = get_row(dir);
    int col_dir = get_col(dir);

    int row_to_check = row + row_dir * (movie_title_size - 1);
    int col_to_check = col + col_dir * (movie_title_size - 1);
    return in_range(row_to_check, col_to_check, num_rows, num_cols);
}

/*
    Second layer of abstraction of the search algorithm. This function is used
   to check every direction from the given location. If such diraction exists
   where the movie title is found, then the direction is returned. Otherwise,
   NONE is returned.
*/
Direction is_movie_in_location(vector<vector<char>> soup, string movie_title,
                               int row, int col) {
    search::debug::search_loc_step(row, col, movie_title);
    int num_rows = soup.size();
    int num_cols = soup[0].size();
    int movie_len = movie_title.size();

    Direction dir_result = Direction::NONE;  // assume is not in location
    for (Direction dir : DIRECTIONS_ARY) {
        if (!is_possible_direction(dir, row, col, num_rows, num_cols,
                                   movie_len)) {
            continue;
        }
        if (is_movie_in_direction(soup, movie_title, row, col, dir)) {
            dir_result = dir;  // proved wrong
            break;
        }
    }
    return dir_result;
}

/*
    This function is needed to make the pattern matching of the movie title case
   insensitive, that way the movie title string is succesfully compared
   one-to-one with the soup of letters.
*/
string format_movie(string movie_title) {
    string formatted = "";
    for (char letter : movie_title) {
        if (isalpha(letter)) {
            char upper_letter = toupper(letter);
            formatted.push_back(upper_letter);
        }
    }
    search::debug::movie_title_formatted(movie_title, formatted);
    return formatted;
}

bool direction_exists(Direction direction) {
    return direction != Direction::NONE;
}

/*
    First layer of abstraction of the search algorithm to check if a given movie
   is in the soup. Essentially calls the is_movie_in_location function for each
   location in the soup of letters.

    Movie titles found are hanled by as a tuple<string, int,int,Direction> where the components are the movie title, the row where the movie title was found, the column where the movie title was found and the direction where the movie title was found correspondingly. If the movie title was not found in the soup of letters, then the tuple returned is NOT_FOUND.
*/
tuple<string, int, int, Direction> is_movie_in_soup(vector<vector<char>> soup,
                                            string movie_title) {
    tuple<string, int, int, Direction> result = NOT_FOUND;
    string formatted = format_movie(movie_title);

    int num_rows = soup.size();
    int num_cols = soup[0].size();
    for (unsigned int row = 0; row < num_rows; row++) {
        for (unsigned int col = 0; col < num_cols; col++) {
            Direction dir = is_movie_in_location(soup, formatted, row, col);
            if (direction_exists(dir)) {
                result = {movie_title, row, col, dir};  // make result tuple with the location and direction
                break;
            }
        }
    }
    return result;
}

bool equal(tuple<string, int, int, Direction> result1,
           tuple<string, int, int, Direction> result2) {
    return get<0>(result1) == get<0>(result2) && get<1>(result1) == get<1>(result2) &&
           get<2>(result1) == get<2>(result2) && get<3>(result1) == get<3>(result2);
}

/*
    Entry point of search algorithm. Essentially this should be the public
   function called exposed to the main application.

    The returned type is a vector of found movies. A found movie is given by a
   tuple where the first component is it's title and the second component is the
   result tuple. The result tuple has the information where the movie title was
   found in the soup of letters, the first component is the row, second column
   and third direction.
*/
vector<tuple<string, int, int, Direction>> search::movies_in_soup(vector<vector<char>> soup, vector<string> movies) {
    vector<tuple<string, int, int, Direction>> movies_found;
    for (string movie_title : movies) {
        tuple<string, int, int, Direction> result = is_movie_in_soup(soup, movie_title);
        if (!equal(result, NOT_FOUND)) {
            tuple<string, int, int, Direction> movie_found = result;
            movies_found.push_back(movie_found);
        }
    }
    return movies_found;
}
// =-------------------------------- END OF SEARCH ALGORITHM
// -----------------------------=
// ========================================================================================


// =----------------- Debugging functions -----------------=
void search::debug::movie_title_formatted(string movie_title, string formatted) {
    if (global::debug_flags::MOVIE_TITLE_FORMATTED) {
        global::fncs::show_msg("DEBUG: formatted movie title: ", formatted);
    }
}

void search::debug::search_loc_step(int row, int col, string movie_title) {
    if (global::debug_flags::SEARCH_LOC_STATE) {
        global::fncs::show_msg("DEBUG: searching for movie: ", movie_title);
        global::fncs::show_msg("DEBUG: at location: ", str_of_loc_pair({row, col}));
    }
}

void search::debug::search_dir_step(string direction, string movie_title) {
    if (global::debug_flags::SEARCH_DIR_STATE) {
        global::fncs::show_msg("DEBUG: searching for movie: ", movie_title);
        global::fncs::show_msg("DEBUG: at direction: ", direction);
    }
}

void search::debug::movie_found(string movie, int row, int col, string direction) {
    if (global::debug_flags::MOVIE_TITLES_TO_SEARCH) {
        global::fncs::show_msg("DEBUG: movie found: ", movie);
        global::fncs::show_msg("DEBUG: at location: ", str_of_loc_pair({row, col}));
        global::fncs::show_msg("DEBUG: at direction: ", direction);
    }
}  // namespace debug

void movie_not_found(string movie) {
    if (global::debug_flags::MOVIE_TITLE_NOT_FOUND) {
        global::fncs::show_msg("DEBUG: movie not found: ", movie);
    }
}

// =----------------- End of debugging functions -----------------=
