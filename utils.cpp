#include "utils.hpp"

float VectDotProduct(const vect& v1, const vect& v2){
    if (v1.size() != v2.size()){
        throw "Vector dot product is not possible with inconsistant vectors\n";
    }
    int elems = v1.size();
    float sum = 0;
    for (int i = 0; i < elems; i++)
    {
        sum += v1[i]*v2[i];
    }
    return sum;
}

matrix RandomMatrix(int rows, int cols){
    matrix M;
    srand(time(0));
    M.reserve(rows*cols);
    for (int r = 0; r < rows; r++)
    {
        M.emplace_back(vect());
        for (int c = 0; c < cols; c++)
        {
            M[r].emplace_back(rand()%10);
        }
    }
    return M;
}