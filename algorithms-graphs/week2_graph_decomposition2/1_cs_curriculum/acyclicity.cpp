#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int counter = 1;
int cyclicity = 0;
unordered_map<int,int> post;

void post_visit(int v){
  post[v] = counter;
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

void explore2(vector<bool> &visited, vector<vector<int> > &adj, const int &v){
  visited[v] = true;
  for (auto w : adj[v])
  {
    if(!visited[w]){
      if(post[v]>post[w]){
        cyclicity = 1;        
      } 
      explore2(visited,adj,w);      
    }
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

void DFS2(vector<vector<int> > &adj){
  vector<bool> visited (adj.size(), false);

  for (size_t v = 0; v < adj.size(); v++)
  {
    if(!visited[v]){
      explore2(visited,adj,v); 
    }
  } 
}

int acyclic(vector<vector<int> > &adj) {
  DFS(adj);
  //DFS2(adj);
  return cyclicity;
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
