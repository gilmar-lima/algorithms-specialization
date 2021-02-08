#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
struct node{
  int value;
  int post;
};

auto comparison = [](node a, node b){
  return a.post < b.post;          
};
priority_queue<node, vector<node>, decltype(comparison)> topo_order (comparison);

int counter = 1;

void post_visit(int v){  
  node current_node {v,counter};
  topo_order.push(current_node);
  counter++;
}

void explore(vector<bool> &visited, vector<vector<int> > &adj, const int &v){
  visited[v] = true;
  for (auto w : adj[v])
  {
    if(!visited[w]){
      explore(visited,adj,w);          
    }
  }
  post_visit(v);  
}

void dfs(vector<vector<int> > &adj){
  vector<bool> visited (adj.size(), false);

  for (size_t v = 0; v < adj.size(); v++)
  {
    if(!visited[v]){
      explore(visited,adj,v); 
    }
  } 
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  dfs(adj);

  int queue_size = topo_order.size();

  for(int i = 0; i<queue_size; i++)
  {
    order.push_back(topo_order.top().value);
    topo_order.pop();
  }

  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
