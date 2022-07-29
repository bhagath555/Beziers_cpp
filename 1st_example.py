import bezier
import matplotlib.pyplot as plt

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