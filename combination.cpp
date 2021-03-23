#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const double INF = 1e200;
const int MAX = 30;
int n;
double dist[MAX][MAX];
double best;
double minEdge[MAX];
vector<int> nearest[MAX];

bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}

bool pathReversePruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	for (int i = 0; i + 3 < path.size(); i++) {
		int p = path[i];
		int a = path[i + 1];
		if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
			return true;
	}
	return false;
}

double simpleHeuristic(vector<bool>& visited) {
	double ret = minEdge[0];
	for (int i = 0; i < n; i++) {
		if (!visited[i])
			ret += minEdge[i];
	}
	return ret;
}

void search(vector<int>& path, vector<bool>visited,
	double currentLength) {
	if (best <= currentLength + simpleHeuristic(visited)) return;
	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

double solve() {
	for (int i = 0; i < n; i++) {
		minEdge[i] = INF;
		for (int j = 0; j < n; j++) {
			if(i !=j) minEdge[i] = min(minEdge[i], dist[i][j]);
		}
	}
	for (int i = 0; i < n; i++) {
		vector<pair<double, int>> order;
		for (int j = 0; j < n; j++)
			if (i != j)
				order.push_back(make_pair(dist[i][j], j));
		sort(order.begin(), order.end());
		nearest[i].clear();
		for(int j=0;j<n;j++){
			nearest[i].push_back(order[j].second);
		}
	}

	best = INF;
	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}


struct DisjointSet {
	DisjointSet(int n);
	int find(int here);
	bool merge(int a, int b);
};
vector<pair<double, pair<int, int>>> edges;

double mstHeuristic(int here, const vector<bool>& visited) {
	DisjointSet sets(n);
	double taken = 0;
	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if (a != 0 && a != here && visited[a]) continue;
		if (b != 0 && b != here & visited[b]) continue;
		if (sets.merge(a, b))
			taken += edges[i].first;
	}
	return taken;
}