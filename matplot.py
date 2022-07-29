import matplotlib.pyplot as plt
import bezier

b = bezier.bezier(2)

b.display()
# 
x = b.evaluate(0,1,50)

cps = b.get_ctrl_pnts()
print(cps)
plt.plot(cps[0], cps[1], 'b--', linewidth = '1.5')
plt.plot(cps[0], cps[1], 'ro')
plt.plot(x[0], x[1], 'k', linewidth = '2')

plt.show()