import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator, FormatStrFormatter

Gamma = 1.4
data = np.loadtxt("output.txt")
data2 = np.loadtxt("riemann.data")

def Rescale(data):
	return np.arange(1, data.shape[0] + 1) * 1.0 / data.shape[0]

x = Rescale(data)
x2 = Rescale(data2)
data[:, 1] = data[:, 3]
data[:, 3] = data[:, 2] / data[:, 0]
data[:, 2] = data[:, 2] * (Gamma - 1.0)
data[:, 2]  = data[:, 2] 
data2[:, 0] = data2[:, 1]
data2[:, 1] = data2[:, 2]
data2[:, 2] = data2[:, 3]
data2[:, 3] = data2[:, 2] / (Gamma - 1.0) / data2[:, 0]
xticks = np.arange(0,1.1,0.1)
yLabels = ["Density", "Velocity", "Pressure", "Specific Internal Energy"]

plt.figure(figsize=(20,12),dpi=600)

for i in range(4):
	ax = plt.subplot(2, 2, i + 1)
	ax.plot(x,data[:, i],'k^')
	ax.plot(x2,data2[:, i],'r')
	ax.set_ylabel(yLabels[i])
	ax.set_xticks(xticks)
	ax.grid(True)
	if i in [0, 1]:
		ax.set_xticklabels([])
	if i in [2, 3]:
		ax.set_xlabel("Position")

plt.subplots_adjust(hspace = 0)
