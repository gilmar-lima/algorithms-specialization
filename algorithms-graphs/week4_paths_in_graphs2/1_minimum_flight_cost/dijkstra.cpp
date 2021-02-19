#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>

using namespace std;

struct node{
  int value;
  int distance;
};

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  unordered_set<int> R;
  vector<int> dist (adj.size(), INT_MAX);
  vector<int> prev (adj.size(), -1);

  auto comparison = [](node a, node b){
    return a.distance > b.distance;          
  };
  priority_queue<node, vector<node>, decltype(comparison)> V (comparison);

  dist[s] = 0;
  node s_node {s,0};
  V.push(s_node);
  
  while(V.size() > 0){
    node v =  V.top();
    unordered_set<int>::const_iterator item = R.find(v.value);
    if(item == R.end()){   

      R.insert(v.value);
      for(size_t i = 0; i < adj[v.value].size(); i++){
        int z = adj[v.value][i];
        if (dist[z] > (dist[v.value] + cost[v.value][i])){
          dist[z] = dist[v.value] + cost[v.value][i];
          prev[z] = v.value;

          node z_node {z,dist[z]};
          V.push(z_node);
        }
      }

    }

    V.pop();    
  }

  return dist[t] == INT_MAX ? -1 : dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
