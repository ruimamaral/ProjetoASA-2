import seaborn as sns
import pandas as pd
import numpy as np
from scipy.special import lambertw

df = pd.DataFrame([
	[1000000, 160],
	[2000000, 300],
	[3000000, 450],
	[4000000, 620],
	[5000000, 780],
	[6000000, 940],
	[7000000, 1080],
	[8000000, 1220],
	[9000000, 1400],
	[10000000, 1550],
	[11000000, 1710],
	[12000000, 1880],
	[13000000, 2020],
	[14000000, 2230],
	[15000000, 2330]],
	columns=["edges", "time"])

sns.set(rc={'figure.figsize':(10,6)})
plot = sns.lineplot(x='edges', y='time', data=df, marker="o", c="#b04c4c")
plot.set_xlabel("Arestas")
plot.set_ylabel("Tempo (ms)")
plot.set_title("Complexidade Temporal")
plot.figure.savefig("ct1.png")

def forward(x):
	with np.errstate(divide='ignore', invalid='ignore'):
		return x * np.log(x) 

def inverse(x):
	return x / lambertw(x)

plot.set_xscale("function", functions=(forward, inverse))
plot.set_title("Complexidade Temporal Com Escala Ajustada")
plot.figure.savefig("ct2.png")
