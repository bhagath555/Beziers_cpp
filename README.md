# Beziers_cpp
 
This project mainly focused to exploit the preformance of CPP computation and python's easy-in-data visualization, to learn and study the spline geometrical properties. This repository is also a practical implementation of CPP knowledge that I have been aquiering over the last couple of weeks. I would like to continue develop this repository in coming days, and make it a standard spline package that compatible with C++ and Python via Pybind11. Now is the early stage of the project, as we progress through time, I hope the repository becomes mature and more functionalities will be added to it. If you are interested please feel free to provide suggestions and raise issues, 

## System setup used:
* Operating System : Windows 10
* Package manager  : MSYS MinGW
* Code editor      : VS Code

I have system setup (Windows only) procedure for developing a C/C++ project in following repositories. Please go through it, If you would like.
* [SystemSetup and gtest](https://github.com/bhagath555/learn-cpp-gtest#setting-up)
* [pybind11](https://github.com/bhagath555/Learn_cpp_pybind11#system-setup)

## Folder Structure:

To summerise this project:
* Developed bezier curve formulation in CPP.
* Used pybind11 to used CPP code in python. 
* This allows to extract the computational efficiency of C++ and Python's data visualization power.
``` 
Beziers_cpp
    ├───.vscode
    ├───binding
    │   ├───bezier_binder.cpp   -> Binding the CPP code in ../src into importabel python module. 
    │   └───CMakeLists.txt      -> To automate the binding process
    ├───build                   -> Generated build directory
    ├───include                 -> All the headers files are stored here
    │   ├───bezier.h            -> Bezier class and it's declaration
    │   └───utils.h             -> Utilities declaration
    ├───src
    │   ├───bezier.cpp          -> Implementation of the bezier functionalities
    │   └───utils.cpp           -> Implementation of dependent functions
    ├───1st_example.py          -> Example tutorial 1
    ├───2nd_example.py          -> Example tutorial 2
    ├───bezier.pyd              -> Generated bezier module
    ├───CMakeLists.txt          -> File that automates the entire building process.
    └───README.md               -> Markdown file to explain the repository.
```


## Usage:
Two examples are provided to demonstrate the usage of the binded code. 

![Usage](https://github.com/bhagath555/thmsgbrt/blob/master/2022-07-29-21-12-36.gif)

### 1_example.py
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

### 2_example.py 

Calculating the basis function values at a particulat parametric value and plotting the basis functions in over parametric space.
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
* Genereting ReadTheDocs format webpage (using Doxygen + Sphinx) from docstrings. 
* Writing unittest to test the code.

## Completed tasks:
* Design basic structure of the project and make simple version with bezier formulation.
* Add bezier class and required class functionalities with proper docstrings.
* Creating python binding of bezier class.
* Add tutorials to explain the bezier modules in python.

## Final Note
Please feel free to suggest your ideas to improve this project via [issues section](https://github.com/bhagath555/Beziers_cpp/issues).

Bhagath Mamindlapelly.
