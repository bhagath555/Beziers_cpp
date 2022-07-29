
#include "bezier.h"


// i^th basis function.
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

bezier::bezier(int p)
{
    degree = p;
    Ctrl_Pnts = RandomMatrix(degree+1, 2);
}

bezier::bezier()
{
    degree = 2;
    Ctrl_Pnts = RandomMatrix(degree+1, 2);
}

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


float bezier::ith_basis(float xi, int i){
    return bezier_ith_basis(degree, xi, i);
}

vect bezier::basis(float xi){
    vect N;
    N.reserve(degree+1);
    for (int i = 0; i < degree+1; i++){
        N.emplace_back(bezier_ith_basis(degree, xi, i));
    }
    return N;
}

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

bezier::~bezier()
{
    std::cout << "Class is Destructor \n";
}

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

void bezier::display(void){
    std::cout << "Bezier curve with degree : " << degree << "\n";
    std::cout << "Control point coordinateds : \n";
    display_cps();
}

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
