#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

vector<int> bfs(vector<vector<int> > &adj, int &s){
  vector<int> dist (adj.size(), INT_MAX);

  dist[s] = 0;
  queue<int> node_queue;
  node_queue.push(s);

  while (!node_queue.empty())
  {
    int u = node_queue.front();
    node_queue.pop();

    for(auto v : adj[u]){
      if(dist[v] == INT_MAX){
        node_queue.push(v);
        dist[v] = dist[u] + 1;
      }
    }
  }

  return dist;
}

int distance(vector<vector<int> > &adj, int s, int t) { 
  
  vector<int> dist = bfs(adj, s);
  if(dist[t] == INT_MAX){
    return -1;
  }else{
    return dist[t];
  }
  
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
