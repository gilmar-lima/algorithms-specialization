#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int counter = 1;
unordered_map<int,int> post, pre;

void post_visit(int v){
  post[v] = counter;
  counter++;
}

void pre_visit(int v){
  pre[v] = counter;
  counter++;
}

void explore(vector<bool> &visited, vector<vector<int> > &adj, const int &v){

  visited[v] = true;
  pre_visit(v);
  for (auto w : adj[v])
  {
    if(!visited[w]){
      explore(visited,adj,w);          
    }
  }
  post_visit(v);
  
}

bool isCyclic(int u, int v){
  if(pre[v]<pre[u] && post[u]<post[v]){
    return true;
  }else{
    return false;
  }
}

void DFS(vector<vector<int> > &adj){
  vector<bool> visited (adj.size(), false);

  for (size_t v = 0; v < adj.size(); v++)
  {
    if(!visited[v]){
      explore(visited,adj,v); 
    }
  } 
}

int checkCyclicity(vector<vector<int> > &adj){
  vector<bool> visited (adj.size(), false);

  for (size_t v1 = 0; v1 < adj.size(); v1++)
  {
    for(auto v2 : adj[v1])
    {
      if(isCyclic(v1, v2)) return 1;       
    }
  }

  return 0;    
}

int acyclic(vector<vector<int> > &adj) {
  DFS(adj);  
  return checkCyclicity(adj);
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
  std::cout << acyclic(adj);
}
