#include<iostream>
#include<vector>
#include<iomanip>
#include<cstdlib>
#include<time.h>
// float bezier_ith_basis(int p, float xi, int i);

typedef std::vector<float> vect;

typedef std::vector<std::vector<float>> Matrix;

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

class bezier
{
private:
    int degree;
    Matrix Ctrl_Pnts;
public:
    bezier(int);
    bezier();
    bezier(const Matrix& cps_in);
    ~bezier();
    float ith_basis(float xi, int i);
    vect basis(float xi);
    Matrix basis(float start, float end, int divs);
    void display_cps(void);
    bool check_ctrl_pnts(const Matrix& cps_in);
    void display(void);
    vect evaluate(float xi);
    Matrix evaluate(float lower, float upper, float divs);
};

bezier::bezier(int p)
{
    degree = p;
}

bezier::bezier()
{
    degree = 2;
}

bezier::bezier(const Matrix& cps_in)
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

bool bezier::check_ctrl_pnts(const Matrix& cps_in){
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

Matrix bezier::basis(float lower, float upper, int divs)
{
    if (divs < 1){
        throw "Number of divisions can't be less than 1";
    }
    Matrix NN;
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

Matrix bezier::evaluate(float lower, float upper, float divs){
    if (divs < 1){
        throw "Number of divisions can't be less than 1";
    }
    Matrix pnt_arr;
    float xi = lower;
    float step_len = (upper-lower)/divs;
    int pnts = divs+1;
    pnt_arr.reserve(2*pnts);
    for (int i = 0; i < pnts; i++)
    {
        vect coords = evaluate(xi);
        pnt_arr.emplace_back(coords);
        xi = xi + step_len;
    }  
    return pnt_arr; 
}



int main(){
    Matrix cps;
    cps = {{1,1},{3,2},{2,1}};
    bezier b(cps);
    b.display();
    vect crds = b.evaluate(0);
    std::cout << "Coordinates at xi = 0 : ";
    for (const auto& i : crds)
    {
        std::cout << i << "    "; 
    }
    std::cout << "\n";
    crds = b.evaluate(1);
    std::cout << "Coordinates at xi = 1 : ";
    for (const auto& i : crds)
    {
        std::cout << i << "    "; 
    }
    std::cout << "\n";   
}