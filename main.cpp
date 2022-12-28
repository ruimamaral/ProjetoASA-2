#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef struct {
	public:
		int u;
		int v;
		int weight;
} edge;

struct cmp_edges {
    bool operator() (const edge &a, const edge &b) const {
        return a.weight < b.weight;
    }
};

int get_predecessor(int v, vector<int> pre) {
	int p = pre[v], pp = pre[p];
	if (pp != p) {
		pre[v] = get_predecessor(pp, pre);
		pre[p] = pre[v];
	}
	return pre[v];
}

void unite(int u, int v, vector<int> pre, vector<int> rank) {
	if (rank[pre[u]] > rank[pre[v]]) {
		pre[v] = pre[u];
	} else if (rank[pre[u]] < rank[pre[v]]) {
		pre[u] = pre[v];
	} else { // If they have the same rank
		pre[u] = pre[v];
		rank[pre[v]]++;
	}
}

int kruskal(vector<int> pre, vector<int> rank, set<edge, cmp_edges> edges) {
	set<edge>::iterator iter;
	int weight = 0;
	for (iter = edges.begin(); iter != edges.end(); iter++) {
		int u = iter->u;
		int v = iter->v;
		if (get_predecessor(u, pre) != get_predecessor(v, pre)) {
			unite(u, v, pre, rank);
			weight += iter->weight;
		}
	}
	return weight;
}

int main() {
	int e, vs;

	cin >> vs;
	cin >> e;

	vector<int> predecessors(vs);
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
		predecessors[i] = i;
		rank[i] = 0;
	}

	cout << kruskal(predecessors, rank, edges) << "\n";
	return 0;
}