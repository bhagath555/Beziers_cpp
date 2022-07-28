#pragma once

// Standard Library
#include<iomanip>
#include<iostream>
#include "utils.hpp"

// Recursive bezier basis function
float bezier_ith_basis(int p, float xi, int i);

// Bezier class
class bezier
{
private:
    int degree;
    matrix Ctrl_Pnts;
    srand(time(0));
public:
    bezier(int);
    bezier();
    bezier(const matrix& cps_in);
    ~bezier();
    float ith_basis(float xi, int i);
    vect basis(float xi);
    matrix basis(float start, float end, int divs);
    void display_cps(void);
    bool check_ctrl_pnts(const matrix& cps_in);
    void display(void);
    vect evaluate(float xi);
    matrix evaluate(float lower, float upper, float divs);
};