# Beziers_cpp
 
This project, mainly focusing on to exploit the preformance of CPP computation and python's easy-in-data visualization, to learn and study the spline geometrical properties. This repository is practical implementation of CPP knowledge I have been aquiering over the last couple of weeks. By this stage, I am pretty confident about my learning. I would like to continue develop this repository in coming days, to make it, a standard spline formulation package. Now is the early stage of the project, as we progress through time, I hope the repository becomes mature and more functionalities will be added to it. 

### System setup used:
* Operating System : Windows 10
* Package manager  : MSYS MinGW
* Code editor      : VS Code

I have system setup (Windows only) procedure for developing a C/C++ project in following repositories. Please go through it, If you would like to.
* Link1
* Link2

To summerise this project:
* Developed bezier curve formulation in CPP.
* Used pybind11 to used CPP code in python. 
* This allows to extract the computational efficiency of C++ and Python's data visualization power.


Bezier curve formulation in CPP with unittests and python binding.

## Usage:
Two examples are provided to demonstrate the usage of the binded code. 
https://drive.google.com/file/d/1_1UrHkD1lzFdAW-S6-5yuMITfFpESVW7/view?usp=drivesdk

1. 1_example.py
* This is to explain the creation of a pth degree bezier object, calculating the point on a curve, and plotting the actual curve and it's control net.
``` python
import matplotlib.pyplot as plt
import bezier

# Degree 3 bezier object.
b = bezier.bezier(3)
# Printig bezier curve information to console.
b.display()

# Evaluating the curve at parametric coordinate xi = 0.5
coords = b.evaluate(0.5)
print("At xi = 0.5, X-coodrinate is ", coords[0], "; Y-coordinate is ", coords[1])

# Evaluating points on the bezier curve, with 50 divisions.
x = b.evaluate_crv(50)

# Accessing control point information from the class.
cps = b.get_ctrl_pnts()

# Plotting control net.
plt.plot(cps[0], cps[1], 'b--', linewidth = '1.5')
plt.plot(cps[0], cps[1], 'ro')
# Plotting the curve.
plt.plot(x[0], x[1], 'k', linewidth = '2')

# plot
plt.show()
```

2. 2_example.py 
* Calculating the basis function values at a particulat parametric value and plotting the basis functions in over parametric space.
``` python
import matplotlib.pyplot as plt
import bezier
# Degree 3 bezier object.
b = bezier.bezier(3)
# Printig bezier curve information to console.
b.display()
# Basis functios at parametric coordinate xi = 0.5
Ni = b.basis(0.5)
print("Basis functions value at xi = 0.5 is ", Ni)
# Plotting bezier basis functions, with 50 divisions
divs = 50
# Parametric space
xi = bezier.ParametricRange(divs)
# Basis functions
N = b.basis(0,1,divs)
# Plotting
plt.plot(xi, N, linewidth = '1.5')
plt.show()
```

## Upcoming task:
* Adding Matrix operations.
* Genereting ReadTheDocs format webpage (using Doxygen + Sphinx) from the docstrings of the code. 
* Writing unittest to test the code.

