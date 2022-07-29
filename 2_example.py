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