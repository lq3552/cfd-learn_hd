#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt

Gamma = 1.4
data = np.loadtxt("riemann.data")
x = np.arange(1,data.shape[0]+1)*1.0/data.shape[0]
