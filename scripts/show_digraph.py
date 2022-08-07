import networkx as nx
import matplotlib.pyplot as plt
n, m = map(int, input().strip().split())
g = nx.MultiDiGraph()
for _ in range(m):
	a, b = map(int, input().strip().split())
	g.add_edge(a, b)
nx.draw_networkx(g, with_labels=True)
plt.show()