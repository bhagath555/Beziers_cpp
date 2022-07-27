#include<iostream>
#include<vector>
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
    ~bezier();
    float ith_basis(float xi, int i);
    vect all_basis(float xi);
    Matrix all_basis_range(float start, float end, int divs);
    
};

bezier::bezier(int p)
{
    degree = p;
}

bezier::bezier()
{
    degree = 2;
}

float bezier::ith_basis(float xi, int i){
    return bezier_ith_basis(degree, xi, i);
}

vect bezier::all_basis(float xi){
    vect N;
    N.reserve(degree+1);
    for (int i = 0; i < degree+1; i++){
        N.emplace_back(bezier_ith_basis(degree, xi, i));
    }
    return N;
}

Matrix bezier::all_basis_range(float lower, float upper, int divs)
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
    std::cout << "Destructor \n";
}

int main(){
    bezier b(3);
    float ni = b.ith_basis(0.5, 3);
    std::cout << ni << "  <-\n";

    Matrix M;
    M = b.all_basis_range(0,1,4);    
    for (const auto& i : M)
    {
        for (const auto& j : i)
        {
            std::cout << j << "   ";
        }
        std::cout << "\n";
    }
    
}