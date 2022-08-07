import networkx as nx
import matplotlib.pyplot as plt
n, m = map(int, input().strip().split())
g = nx.MultiGraph()
for _ in range(m):
	a, b, c = map(int, input().strip().split())
	g.add_edge(a, b, weight=c)
pos = nx.spring_layout(g)
nx.draw(g, pos, with_labels=True)
nx.draw_networkx_edge_labels(g, pos)
plt.show()