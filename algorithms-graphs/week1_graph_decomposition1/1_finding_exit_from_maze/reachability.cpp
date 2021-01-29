#include <iostream>
#include <vector>

using namespace std;

void explore(vector<bool> &visited, vector<vector<int> > &adj, const int &x){

  visited[x] = true;

  for (auto w : adj[x])
  {
    if(!visited[w]){
      explore(visited,adj,w);
    }
  }
}

int reach(vector<vector<int> > &adj, int x, int y) {
  vector<bool> visited (adj.size(), false);
  
  explore(visited,adj,x);

  if(visited[y]) return 1;

  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  cin >> x >> y;
  cout << reach(adj, x - 1, y - 1);
}
