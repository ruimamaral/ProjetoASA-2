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

vector<edge> result;

struct cmp_edges {
	bool operator() (const edge &a, const edge &b) const {
		return a.weight > b.weight;
	}
};

int get_head(int v, vector<int> &head) {
	int p = head[v],
		pp = head[p];
	if (pp != p) {
		head[v] = get_head(pp, head);
		head[p] = head[v];
	}
	return head[v];
}

void unite(int u, int v, vector<int> &head, vector<int> &rank) {
	if (rank[u] > rank[v]) {
		head[v] = head[u];
	} else if (rank[u] < rank[v]) {
		head[u] = head[v];
	} else { // If they have the same rank
		head[u] = head[v];
		rank[v]++;
	}
}

int kruskal(vector<int> &head, vector<int> &rank, vector<edge> &edges) {
	vector<edge>::iterator iter;
	int weight = 0;
	for (iter = edges.begin(); iter != edges.end(); iter++) {
		int u = iter->u;
		int v = iter->v;
		int pu = get_head(u, head);
		int pv = get_head(v, head);
		if (pu != pv) {
			unite(pu, pv, head, rank);
			weight += iter->weight;
			result.push_back(*iter);
		}
	}
	return weight;
}

int main() {
	int e, vs;

	scanf("%d\n%d\n", &vs, &e);

	if (vs == 0 || e == 0) {
		printf("%d\n", 0);
		return 0;
	}

	vector<int> heads(vs + 1);
	vector<int> rank(vs + 1);
	vector<edge> edges(e);

	for (int i = 0; i < e; i++) {
		edge *new_edge;
		int u, v, w;
		scanf("%d %d %d\n", &u, &v, &w);
		new_edge = new edge {u, v, w};
		edges[i] = ((*new_edge));
	}

	sort(edges.begin(), edges.end(), cmp_edges());

	for (int i = 0; i < vs + 1; i++) {
		heads[i] = i;
		rank[i] = 0;
	}

	printf("%d\n", kruskal(heads, rank, edges));
	return 0;
}