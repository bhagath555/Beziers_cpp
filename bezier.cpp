/**
 * @file bezier.cpp
 * @author your name (you@domain.com)
 * @brief This file containing all the code that required to implement bezier class. NOTE: This documentions is still in development.
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "bezier.h"


/**
 * @brief Calculates the ith basis function value at give parametric value, xi, of degree p bezier curve.
 * 
 * @param p Degree.
 * @param xi Parametric value in {0, 1}.
 * @param i Basis function index.
 * @return (float) Basis function value at xi.
 */
float bezier_ith_basis(int p, float xi, int i)
{
    if (p == 0){
        if (i==0){
            return 1.0;
        }
        else{
            return 0.0;
        }
    }
    else{
        if (i<0 | i> p+1){
            return 0;
        }
        else{
            return xi * bezier_ith_basis(p-1, xi, i-1) + (1 - xi) * bezier_ith_basis(p-1, xi, i);
        }
    }
}

/**
 * @brief Construct a new bezier::bezier object. Bezier degree is user's choice, but random control points coordinates will be generated automatically.
 * 
 * @param p Degree of the curve.
 */
bezier::bezier(int p)
{
    degree = p;
    Ctrl_Pnts = RandomMatrix(degree+1, 2);
}

/**
 * @brief Construct a new bezier::bezier object. In this object generation, default degree will be considered as 2, and random control points coordinates will be generated automatically.
 * 
 */
bezier::bezier()
{
    degree = 2;
    Ctrl_Pnts = RandomMatrix(degree+1, 2);
}

/**
 * @brief Construct a new bezier::bezier object. Bezier control points are inputs. Each row correspond to a control point and columns consist coordinate values.
 * 
 * @param cps_in Bezier control points.
 */
bezier::bezier(const matrix& cps_in)
{
    bool valid = check_ctrl_pnts(cps_in);
    if (!valid){
        throw "Please enter valid control points.";
    }
    else
    {
        int rows = cps_in.size();
        Ctrl_Pnts.reserve(rows*2);
        for (int i = 0; i < rows; i++)
        {
            Ctrl_Pnts.emplace_back(vect());
            for (int j = 0; j < 2; j++)
            {
                Ctrl_Pnts[i].emplace_back(cps_in[i][j]);
            }  
        }
        degree = rows-1;        
    }
}

/**
 * @brief This functions checks the validity of a input bezier control points array.
 * 
 * @param cps_in Matrix, Each row correspond to a control point and columns representing X-Y coodinate values.
 * @return true If given matrix is valid bezier control net.
 * @return false If the given matrix is invalid bezier control net.
 */
bool bezier::check_ctrl_pnts(const matrix& cps_in){
    int rows = cps_in.size();
    if (rows < 2){
        // throw "Number of control points should be at least 2\n";
        return false;
    }
    // int cols = cps_in[0].size();
    int coords = 2;
    for (const auto& i:cps_in)
    {
        if (i.size() < coords)
        {
            // throw "Inconsistant control points are entered\n";
            return false;
        }
    }
    return true;
}

/**
 * @brief ${i}^{th} basis function value, where i in {0, degree}.
 * 
 * @param xi parametric value in {0,1}
 * @param i basis index in {0, degree}
 * @return float pth degree ith bezier basis value at xi.
 */
float bezier::ith_basis(float xi, int i){
    return bezier_ith_basis(degree, xi, i);
}

/**
 * @brief Returns a vector all bezier basis value of degree p bezier curve, at parametric coordinate xi {0,1}. 
 * 
 * @param xi Parametric coordinate, should be within {0,1}
 * @return vect Vector of degree+1 basis function value at xi.
 */
vect bezier::basis(float xi){
    vect N;
    N.reserve(degree+1);
    for (int i = 0; i < degree+1; i++){
        N.emplace_back(bezier_ith_basis(degree, xi, i));
    }
    return N;
}

/**
 * @brief Calculates the bezier basis function matrix, each row correspond to bezier basis set at each parametric value. First set of basis functions are calculated at parametric value lower, and last set of basis functions are calculated at parametric value upper. Inbetween parametric values unifromly devided based on the number of divsions (divs). 
 * 
 * @param lower Lower parametric coordinate.
 * @param upper Upeer parametric coordinate.
 * @param divs Number of divisions.
 * @return matrix Bezier basis matrix, each row correspond to the basis function set at paremetric value.
 */

matrix bezier::basis(float lower, float upper, int divs)
{
    if (divs < 1){
        throw "Number of divisions can't be less than 1";
    }
    matrix NN;
    float xi = lower;
    float step_len = (upper-lower)/divs;
    int pnts = divs+1;
    NN.reserve((degree+1)*pnts);
    for (int i = 0; i < pnts; i++)
    {
        NN.emplace_back(vect());
        for (int j = 0; j < degree+1; j++){
            NN[i].emplace_back(bezier_ith_basis(degree, xi, j));
        }
        xi = xi + step_len;
    }
    return NN;
}

/**
 * @brief Prints control point coordinate values of bezier object.
 * 
 */
void bezier::display_cps(void){
    // int rows  = Ctrl_Pnts.size();
    // int cols  = Ctrl_Pnts[0].size();
    for (const auto& r: Ctrl_Pnts)
    {
        for (const auto& c: r)
        {
            std::cout << c << std::setw(10);
        }
        std::cout << '\n';
    }
}

/**
 * @brief Prints the bezier object field information.
 * 
 */
void bezier::display(void){
    std::cout << "Bezier curve with degree : " << degree << "\n";
    std::cout << "Control point coordinates : \n";
    display_cps();
}

/**
 * @brief Evalue the bezier curve coordinates at given parametric coordinate (xi).
 * 
 * @param xi Parametric coordinate {0,1}. 
 * @return vect Vector of size 2. First element correspond to x coordinate and second element correspond to y coordinate.
 */
vect bezier::evaluate(float xi){
    vect N = basis(xi);
    vect coords;
    coords.reserve(2);
    float sum;
    for (int x = 0; x < 2; x++)
    {
        sum = 0;
        for (int i = 0; i < degree+1; i++)
        {
            sum += N[i] * Ctrl_Pnts[i][x];   
        }
        coords.emplace_back(sum);
    }  
    return coords; 
}

/**
 * @brief Calculates the bezier coordinate values in the given parametric range (lower to upper)
 * 
 * @param lower Lower parametric coordinate.
 * @param upper Upper parametric coordinate.
 * @param divs Number of divisions between the given prametric limits.
 * @return matrix Matrix of size (2,divs+1). First row correspond to x coodinate of curve at series of parametric values. Second row correspond to the y coordinate of curve at series of parametric values.
 */
matrix bezier::evaluate(float lower, float upper, int divs){
    if (divs < 1){
        throw "Number of divisions can't be less than 1";
    }
    float xi = lower;
    float step_len = (upper-lower)/divs;
    int pnts = divs+1;
    vect coords;
    matrix pnt_arr;
    vect x;
    vect y;
    x.reserve(pnts);
    y.reserve(pnts);
    pnt_arr.reserve(2*pnts);

    for (int i = 0; i < pnts; i++)
    {
        coords = evaluate(xi);
        x.emplace_back(coords[0]);
        y.emplace_back(coords[1]);
        xi = xi + step_len;
    }  
    pnt_arr.emplace_back(x);
    pnt_arr.emplace_back(y);
    return pnt_arr; 
}

/**
 * @brief Calculates the bezier curve coordinates at provided number of divsions in range(0,1).
 * 
 * @param divs divisions of bezier curve.
 * @return matrix Bezier curve coordinates matrix.
 */
matrix bezier::evaluate_crv(int divs){
    return evaluate(0,1,divs);
}

/**
 * @brief This function returns the control point coordinates matrix (2,no. of control points) of given bezier curve.
 * 
 * @return matrix Control net of size (2, degree+1).
 */
matrix bezier::get_ctrl_pnts(){
    matrix cps;
    int cp_count = degree+1;
    cps.reserve(2*cp_count);
    vect x;x.reserve(cp_count);
    vect y;y.reserve(cp_count);
    for (int i = 0; i < Ctrl_Pnts.size(); i++)
    {
        x.emplace_back(Ctrl_Pnts[i][0]);
        y.emplace_back(Ctrl_Pnts[i][1]);

    }
    
    cps.emplace_back(x);
    cps.emplace_back(y);
    return cps;
}
