import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator, FormatStrFormatter

Gamma = 1.4
data = np.loadtxt("output.txt")
data2 = np.loadtxt("riemann.data");
x = np.arange(1,data.shape[0]+1)*1.0/data.shape[0]
x2 = np.arange(1,data2.shape[0]+1)*1.0/data2.shape[0]
xticks = np.arange(0,1.1,0.1)

plt.figure(figsize=(20,12),dpi=600)

ax = plt.subplot(2,2,1)
plt.plot(x,data[:,0],'k^')
plt.plot(x2,data2[:,1],'r')
plt.ylabel('Density')
ax.set_xticks(xticks)
ax.set_xticklabels([])
ax.grid(True)

ax = plt.subplot(2,2,3)
plt.plot(x,data[:,2]*(Gamma-1),'k^')
plt.plot(x2,data2[:,3],'r')
plt.xlabel('Position')
plt.ylabel('Pressure')
ax.set_xticks(xticks)
ax.grid(True)

ax = plt.subplot(2,2,2)
plt.plot(x,data[:,3],'k^')
plt.plot(x2,data2[:,2],'r')
plt.ylabel('Velocity')
ax.set_xticks(xticks)
ax.set_xticklabels([])
ax.grid(True)

ax = plt.subplot(2,2,4)
plt.plot(x,data[:,2]/data[:,0],'k^')
plt.plot(x2,data2[:,3]/(Gamma-1)/data2[:,1],'r')
plt.xlabel('Position')
plt.ylabel('Specific Internal Energy')
ax.set_xticks(xticks)
ax.grid(True)

plt.subplots_adjust(hspace = 0)
plt.savefig("result.png", dpi = 600)
