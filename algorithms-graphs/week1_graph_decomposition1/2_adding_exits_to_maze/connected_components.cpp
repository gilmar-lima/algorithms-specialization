#include <iostream>
#include <vector>

using namespace std;

void explore(vector<bool> &visited, vector<vector<int> > &adj, const int &v){

  visited[v] = true;

  for (auto w : adj[v])
  {
    if(!visited[w]){
      explore(visited,adj,w);      
    }
  }
}

int DFS(vector<vector<int> > &adj){
  int cc = 0;
  vector<bool> visited (adj.size(), false);

  for (size_t v = 0; v < adj.size(); v++)
  {
    if(!visited[v]){
      explore(visited,adj,v); 
      cc++;     
    }
  } 
  return cc;
}

int number_of_components(vector<vector<int> > &adj) {
  return DFS(adj);
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
