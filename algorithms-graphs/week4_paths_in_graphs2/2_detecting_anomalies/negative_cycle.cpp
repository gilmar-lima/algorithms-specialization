#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  queue<int> node_queue; 
  vector<bool> visited (adj.size(), false); 
  
  for(int vertex = 0; vertex < adj.size(); vertex++){
    if(visited[vertex] == false){
      vector<int> dist (adj.size(), INT_MAX);
      dist[vertex]  = 0;

      for(size_t r = 0; r < adj.size() - 1; r++){
      bool changed = false;
      unordered_set<int> R;
      node_queue.push(vertex);
      visited[vertex] = true;

      while (!node_queue.empty()){
        
        int u = node_queue.front();
        node_queue.pop();

        for(size_t i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          int previous = dist[v];

          //MAke the calculations only for nodes not visited
          unordered_set<int>::const_iterator item = R.find(v);
          if(item == R.end()){
            R.insert(v);

            node_queue.push(v);
            visited[vertex] = true;
            dist[v] = min(dist[v], dist[u] + cost[u][i]);

            //check if value was updated on last iteration
            bool is_last_iteration = r == adj.size() - 2;
            bool dist_updated = dist[v] < previous;

            if(is_last_iteration && dist_updated){
              return 1;
            }

            changed = dist_updated ? true : changed;
          }    
        }
      }
      R.clear();
      if(!changed) break;

    }
    }
  }

  

  
  return 0;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
