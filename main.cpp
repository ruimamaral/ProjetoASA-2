#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef struct {
	int u;
	int v;
	int weight;
} edge;

struct cmp_edges {
	bool operator() (const edge &a, const edge &b) const {
		return a.weight < b.weight;
	}
};

int get_head(int v, vector<int> &head) {
	int p = head[v], pp = head[p];
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

int kruskal(vector<int> &head, vector<int> &rank, set<edge, cmp_edges> &edges) {
	set<edge>::iterator iter;
	int weight = 0;
	for (iter = edges.begin(); iter != edges.end(); iter++) {
		int u = iter->u;
		int v = iter->v;
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

	vector<int> heads(vs);
	vector<int> rank(vs);
	set<edge, cmp_edges> edges;

	for (int i = 0; i < e; i++) {
		edge *new_edge;
		int u, v, w;
		cin >> u;
		cin >> v;
		cin >> w;
		new_edge = new edge {u, v, w};
		edges.insert((*new_edge));
	}
	for (int i = 0; i < vs; i++) {
		heads[i] = i;
		rank[i] = 0;
	}

	cout << kruskal(heads, rank, edges) << "\n";
	return 0;
}