//
// Created by diejo on 10/8/2023.
//

#ifndef WORD_SEARCH_PPM_STREAM_H
#define WORD_SEARCH_PPM_STREAM_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "dmath.h"
#include "fields.h"
#include "global.h"
#include "input.h"

using namespace std;
using namespace global;

/*
 * The ppm stream is the output stream for the heat map of the soup of letters. It processes the soup field and outputs the heat map representation to a ppm file.
 *
 * A heat map is a representation of the movie titles found in the soup of letters where each letter has a "temperature" based on the number of times it was used to form a movie title. Red is for positions close to letters and blue is the absence of letters.
 */
namespace ppm_stream {
const int MAX_COLOR = 255;

namespace debug {
void heat_map(const vector<vector<int>> &heat_map) {
    if (global::debug_flags::HEAT_MAP) {
        cout << "heat map:" << endl;
        for (const vector<int> &row : heat_map) {
            for (double rgb : row) {
                cout << rgb << " ";
            }
            cout << endl;
        }
    }
}
}  // namespace debug

namespace error {
void output_file(string &ppm_file_validated) {
    fncs::show_msg(msgs::PROGRAM_FAILED, "could not open file: " + ppm_file_validated);
    exit(1);
}
}  // namespace error

void write_rgb(ofstream &out_file, int r, int g, int b) {
    out_file << setw(3) << setfill('0') << r << " ";
    out_file << setw(3) << setfill('0') << g << " ";
    out_file << setw(3) << setfill('0') << b << "  ";
}

void write_comment(ofstream &out_file, const string &comment) {
    out_file << "# " << comment << endl;
}

void write_magic_num(ofstream &out_file, const string &magic_num) {
    write_comment(out_file, "magic number for PPM file");
    out_file << magic_num << endl;
}

void write_dim(ofstream &out_file, int rows, int cols) {
    write_comment(out_file, "dimensions of the image");
    out_file << rows << "  " << cols << endl;
}

void write_max_color(ofstream &out_file, int max_color) {
    write_comment(out_file, "maximum color value");
    out_file << max_color << endl;
}

/*
 * Complementary function to build the ofstream ppm file, where the returned ofstream object is then used to write the rgb values to output the ppm file.
 */
ofstream create_ppm(const vector<vector<double>> &soup_field) {
    string ppm_file_name = input::get_user_input(global::msgs::ENTER_PPM_FILE_NAME);
    string ppm_file_validated = input::validate_output(ppm_file_name);
    ofstream out_file(ppm_file_validated);

    if (!out_file.is_open()) {
        error::output_file(ppm_file_validated);
    }
    global::fncs::show_msg(global::msgs::WRITING_PPM_FILE);
    write_magic_num(out_file, "P3");
    write_dim(out_file, soup_field.size(), soup_field[0].size());
    write_max_color(out_file, MAX_COLOR);
    return out_file;
}

/*
 * Basically the operator of a field (vector<vector<double>>) to a color map (vector<vector<int>>) where int is within the range of -255 to 255.
 *
 * Note that this type of rgb mapping only produces two colors and the shades in between them going through black.
 *
 * A line function is used to map the double values between 0 and 0.5 to the range of 0 to -255. A sigmoid which is more suitable and produces a smoother transition, is used to map the values between 0.5 and the max value on the field.
 *
 * I considered others functions for 0 to 0.5 but linear was the simplest and I didn't want to overcomplicate things.
 */
int field_map_rgb(double weight, double max_weight) {
    double range = 2 * MAX_COLOR;
    double vertical_shift = MAX_COLOR;
    double horizontal_shift = 0.5;
    double lambda = M_PI / max_weight;
    int rgb;
    if (weight == 0.5) {
        rgb = 0;
    } else if (weight < 0.5) {
        double result = -dmath::fncs::line(weight, range, vertical_shift);
        rgb = lround(result);
    } else {
        double result = dmath::fncs::sigmoid(weight, range, vertical_shift, horizontal_shift, lambda);
        rgb = lround(result);
    }
    return rgb;
}

/*
 * Helper function to initialize a fresh rgb matrix out of the dimensions of the soup field.
 */
vector<vector<int>> init_rgb_matrix(const vector<vector<double>> &soup_field) {
    vector<vector<int>> rgb_matrix(soup_field.size(), vector<int>(soup_field[0].size(), 0));
    return rgb_matrix;
}

vector<vector<int>> heat_map_of(const vector<vector<double>> &soup_field) {
    vector<vector<int>> heat_map = init_rgb_matrix(soup_field);
    double max_weight = dmath::fncs::max(soup_field);
    for (int row = 0; row < soup_field.size(); row++) {
        for (int col = 0; col < soup_field[0].size(); col++) {
            double weight = soup_field[row][col];
            heat_map[row][col] = field_map_rgb(weight, max_weight);
        }
    }
    debug::heat_map(heat_map);
    return heat_map;
}

/*
 * Called by main to create the heat map of the soup of letters.
 */
void create_heat_map(const vector<vector<double>> &soup_field) {
    ofstream out_file = create_ppm(soup_field);
    vector<vector<int>> heat_map = heat_map_of(soup_field);
    for (const vector<int> &row : heat_map) {
        for (int rgb : row) {
            if (rgb == 0) {
                write_rgb(out_file, 0, 0, 0);
            } else if (rgb > 0) {
                write_rgb(out_file, rgb, 0, 0);
            } else {
                write_rgb(out_file, 0, 0, abs(rgb));
            }
        }
        out_file << endl;
    }
    out_file.close();
    global::fncs::show_msg(global::msgs::PPM_FILE_CREATED);
}
}  // namespace ppm_stream

#endif  // WORD_SEARCH_PPM_STREAM_H
