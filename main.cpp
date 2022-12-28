#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
	int u;
	int v;
	int weight;
} edge;

struct cmp_edges {
	bool operator() (const edge &a, const edge &b) const {
		return a.weight > b.weight;
	}
};

int get_head(int v, vector<int> &head) {
	int p = head[v],
		pp = head[p];
	printf("%d, %d cona \n", v, p);
	if (pp != p) {
		head[v] = get_head(pp, head);
		head[p] = head[v];
	}
	return head[v];
}

void unite(int u, int v, vector<int> &head, vector<int> &rank) {
	if (rank[head[u]] > rank[head[v]]) {
		head[v] = head[u];
	} else if (rank[head[u]] < rank[head[v]]) {
		head[u] = head[v];
	} else { // If they have the same rank
		head[u] = head[v];
		rank[head[v]]++;
	}
}

int kruskal(vector<int> &head, vector<int> &rank, vector<edge> &edges) {
	vector<edge>::iterator iter;
	int weight = 0;
	for (iter = edges.begin(); iter != edges.end(); iter++) {
		printf("%d, %d, %d alive\n", iter->u, iter->v, iter->weight);
		int u = iter->u;
		int v = iter->v;
		printf("%d %d banana \n", u, v);
		if (get_head(u, head) != get_head(v, head)) {
			unite(u, v, head, rank);
			weight += iter->weight;
		}
	}
	return weight;
}

int main() {
	int e, vs;

	cin >> vs;
	cin >> e;
	printf("%d, %d stop\n", e, vs);

	vector<int> heads(vs + 1);
	vector<int> rank(vs + 1);
	vector<edge> edges(e);

	for (int i = 0; i < e; i++) {
		edge *new_edge;
		int u, v, w;
		cin >> u;
		cin >> v;
		cin >> w;
		new_edge = new edge {u, v, w};
		edges[i] = ((*new_edge));
		printf("%d, %d, %d\n", new_edge->u, new_edge->v, new_edge->weight);
	}

	sort(edges.begin(), edges.end(), cmp_edges());

	for (int i = 0; i < vs + 1; i++) {
		heads[i] = i;
		rank[i] = 0;
	}
	for (int i = 0; i < vs + 1; i++) {
		cout << heads[i];
		cout << rank[i] << "\n";
	}
	vector<edge>::iterator iter;
	for (iter = edges.begin(); iter != edges.end(); iter++) {
		printf("%d, %d, %d here\n", iter->u, iter->v, iter->weight);
	}

	cout << kruskal(heads, rank, edges) << " gay\n";
	return 0;
}