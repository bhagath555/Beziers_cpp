#include "utils.hpp"

/**
 * @brief Vector dot product computation.
 * 
 * @param v1 Vector 1.
 * @param v2 Vector 2.
 * @return float V1.v2
 */
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

/**
 * @brief This function generates a random matrix of required size.
 * 
 * @param rows Number of rows.
 * @param cols Number of columns.
 * @return matrix Random matrix with required dimensions.
 */
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

vect ParametricRange(int divs){
    vect v;
    int pnts = divs+1;
    v.reserve(pnts);
    for (int  i = 0; i < pnts; i++)
    {
        v.emplace_back(float(i)/divs);
    }
    return v;
}