import matplotlib.pyplot as plt
import bezier

# Degree 3 bezier object.
b = bezier.bezier(3)
# Printig bezier curve information to console.
b.display()

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