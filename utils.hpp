#pragma once

// Standard Libraries
#include<vector>
#include<cstdlib>
#include<time.h>

// Custome data types
// Vector
typedef std::vector<float> vect;
// Matrix
typedef std::vector<std::vector<float>> matrix;

float VectDotProduct(const vect& v1, const vect& v2);

matrix RondomMatrix(int rows, int cols);

