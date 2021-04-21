#include <iostream>
#include <vector>
#include <climits>
#include <queue>

using namespace std;

vector<vector<int> > adj;
vector<vector<int>> capacity;
vector<vector<int>> flows;

int bfs(int s, int t, vector<int>& parent) {
				fill(parent.begin(), parent.end(), -1);
				parent[s] = -2;
				queue<pair<int, int>> q;
				q.push({s, INT_MAX});

				while (!q.empty()) {
								int cur = q.front().first;
								int flow = q.front().second;
								q.pop();

								for (int next : adj[cur]) {
												if (parent[next] == -1 && capacity[cur][next]) {
																parent[next] = cur;
																int new_flow = min(flow, capacity[cur][next]);
																if (next == t)
																				return new_flow;
																q.push({next, new_flow});
												}
								}
				}

				return 0;
}

int maxflow(int s, int t) {
				int flow = 0;
				vector<int> parent(adj.size());
				int new_flow;

				while (new_flow = bfs(s, t, parent)) {
								flow += new_flow;
								int cur = t;
								while (cur != s) {
												int prev = parent[cur];
												capacity[prev][cur] -= new_flow;
												flows[prev][cur] += new_flow;
												capacity[cur][prev] += new_flow;
												cur = prev;
								}
				}

				return flow;
}

void read_data() {
				int vertex_count, edge_count;
				std::cin >> vertex_count >> edge_count;
				
				vector<vector<int> > adj_input(vertex_count, vector<int>());
				vector<vector<int> > capacity_input(vertex_count, vector<int>(vertex_count,0));

				adj = adj_input;
				capacity = capacity_input;
				flows = capacity_input;

				for (int i = 0; i < edge_count; ++i) {
						int x, y, edge_capacity;
						std::cin >> x >> y >> edge_capacity;
						adj[x - 1].push_back(y - 1);
						capacity[x - 1][y - 1] =  edge_capacity + capacity[x - 1][y - 1];
						adj[y - 1].push_back(x - 1);
				}
				
}

int main() {
				std::ios_base::sync_with_stdio(false);
				read_data();

				std::cout << maxflow(0, adj.size() - 1) << "\n";
				return 0;
}
