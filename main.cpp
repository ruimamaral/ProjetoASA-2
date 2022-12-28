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
	printf("%d, %d p and pp\n", p, pp); 
	if (pp != p) {
		head[v] = get_head(pp, head);
		head[p] = head[v];
	}
	printf("%d, %d cona  %d\n", v, p, head[v]);
	return head[v];
}

void unite(int u, int v, vector<int> &head, vector<int> &rank) {
	printf("%d, %d, UNITING\n", u, v);
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
		printf("SOLVING %d, %d, %d alive\n", iter->u, iter->v, iter->weight);
		int u = iter->u;
		int v = iter->v;
		printf("%d %d banana \n", u, v);
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
	for (iter = result.begin(); iter != result.end(); iter++) {
		printf("%d, %d, after\n", iter->u, iter->v);
	}
	return 0;
}