//
// Created by diejo on 10/8/2023.
//

#ifndef WORD_SEARCH_MATH_H
#define WORD_SEARCH_MATH_H

#include <string>
#include <tuple>
#include <vector>
#include <cmath>

#include "global.h"

namespace math {
    namespace debug {
        void line(double x, double range, double vertical_shift);
        void sigmoid(double x, double range, double vertical_shift, double horizontal_shift, double lambda);
    }

    namespace fncs {
        double sigmoid(double x, double range, double vertical_shift, double horizontal_shift, double lambda) {
            double power = -lambda * (x - horizontal_shift);
            debug::sigmoid(x, range, vertical_shift, horizontal_shift, lambda);
            return (range / (1 + exp(power))) - vertical_shift;
        }

        double line(double x, double range, double vertical_shift) {
            return (-range * x) + vertical_shift;
        }

        double max(vector<vector<double>> matrix) {
            double max = 0;
            for (const vector<double> &row: matrix) {
                for (double weight: row) {
                    if (weight > max) {
                        max = weight;
                    }
                }
            }
            return max;
        }

        int pair_dot(pair<int, int> p1, pair<int, int> p2) {
            return p1.first * p2.first + p1.second * p2.second;
        }

        double pair_dot(pair<double, double> p1, pair<double, double> p2) {
            return p1.first * p2.first + p1.second * p2.second;
        }

        double pair_magnitude(pair<int, int> p) {
            return sqrt(pair_dot(p, p));
        }

        pair<double, double> pair_normalize(pair<int, int> p) {
            double magnitude = pair_magnitude(p);
            return make_pair(p.first / magnitude, p.second / magnitude);
        }

        double how_much_in_dir(pair<int, int> dir1, pair<int, int> dir2) {
            pair<double, double> norm_dir1 = pair_normalize(dir1);
            pair<double, double> norm_dir2 = pair_normalize(dir2);
            double dot = pair_dot(norm_dir1, norm_dir2);
            return dot;
        }
    }

    void debug::line(double x, double range, double vertical_shift) {
        if (global::debug_flags::LINE) {
            double result = fncs::line(x, range, vertical_shift);
            cout << "DEBUG: line(x, " << range << ", " << vertical_shift << ") = " << result << endl;
        }
    }

    void debug::sigmoid(double x, double range, double vertical_shift, double horizontal_shift, double lambda) {
        if (global::debug_flags::SIGMOID) {
            double result = fncs::sigmoid(x, range, vertical_shift, horizontal_shift, lambda);
            cout << "DEBUG: sigmoid(x, " << range << ", " << vertical_shift << ", " << horizontal_shift << ", " << lambda << ") = " << result << endl;
        }
    }
}


#endif //WORD_SEARCH_MATH_H
