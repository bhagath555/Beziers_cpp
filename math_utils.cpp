#include<iostream>
using namespace std;

class matrix
{
private:
    int rows;
    int cols;
protected:
    
    // Declaring an array of pointer.
    float **grid;
public:
    matrix(int x, int y);
    ~matrix();
    void display(void);
    // float* extract_row(int i_r);
};

matrix::matrix(int x, int y)
{
    rows = x;
    cols = y;
    // dynamically create an array of pointers of size 'rows'.
    grid = new float*[rows];
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new float[cols];
    }
    
    float count = 0.5;
    for (int r = 0; r < x; r++)
    {
        for (int c = 0; c < y; c++)
        {
            grid[r][c] = ++count;
        }
    }
}

matrix::~matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete [] grid[i];
    }
    // [] symbol is used to tell compiler that the variable is an array.
    delete [] grid; 
    
}

void matrix::display(void){
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            cout << grid[r][c] << "        ";
        }
        cout << '\n';
    }
    
}

class control_points2d : protected matrix
{
private:
    int degree;
    const int rows = degree+1;
    const int cols = 2;
    float **grid;
public:
    control_points2d(/* args */);
    ~control_points2d();
};

control_points2d::control_points2d(int p)
{
    degree = p;
    grid = new float*[rows];
    for (int r = 0; r < rows; r++)
    {
        grid[r] = new float[cols];
    }

    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            
        }
        
    }
    
    

}

control_points2d::~control_points2d()
{
}


// float* matrix::extract_row(int i_r){
//     float* p = new float[cols];
//     for (int c = 0; c < cols; c++)
//     {
//         p[c] = grid[i_r][c];
//     }
//     return p;
// }

int main(){
    matrix m(3,4);
    m.display();
    
}
