#include <bits/stdc++.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

stack<int> dfs_stack(vector<vector<int> > &adj);
void explore_stack(vector<bool> &visited, vector<vector<int> > &adj,const int &v, stack<int> &store);
int variable_to_vertex(int variable, int numVars);
vector<vector<int>> reverse_graph(vector<vector<int>> implication_graph);
void explore_scc(vector<bool> &visited, vector<vector<int> > &reversed, int &v, unordered_set<int> &scc);
vector<unordered_set<int>> dfs_scc(vector<vector<int>> &reverserd, stack<int> store);

vector<unordered_set<int>> SCC(vector<vector<int>> implication_graph){
	stack<int> store = dfs_stack(implication_graph);
	vector<vector<int>> reversed = reverse_graph(implication_graph);
	vector<unordered_set<int>> sccs = dfs_scc(reversed, store);
	return sccs;
}

void explore_scc(vector<bool> &visited, vector<vector<int> > &reversed, int &v, unordered_set<int> &scc){

  visited[v] = true;
	scc.insert(v);

  for (auto w : reversed[v])
  {
    if(!visited[w]){
      explore_scc(visited,reversed,w,scc);      
    }
  }
	return;
}

vector<unordered_set<int>> dfs_scc(vector<vector<int>> &reverserd, stack<int> store){
  vector<bool> visited (reverserd.size(), false);
	vector<unordered_set<int>> sccs;
	unordered_set<int> scc;

  while(!store.empty())
  {
    if(visited[store.top()]){
			store.pop();
			continue;
		}
    explore_scc(visited,reverserd,store.top(), scc);
		sccs.push_back(scc);
		scc.clear();
  } 
  return sccs;
}

vector<vector<int>> reverse_graph(vector<vector<int>> implication_graph){
	vector<vector<int>> reversed (implication_graph.size());

	auto reverse_vertex = [&implication_graph, &reversed](int v){
		for(auto vertex : implication_graph[v]){
			reversed[vertex].push_back(v);			
		}
	};

	for(int v = 0; v < implication_graph.size(); v++){
		reverse_vertex(v);		
	}
	return reversed;
}

stack<int> dfs_stack(vector<vector<int> > &adj){
  stack<int> store;
  vector<bool> visited (adj.size(), false);

  for (size_t v = 0; v < adj.size(); v++)
  {
    if(visited[v]) continue;
    explore_stack(visited,adj,v, store);
  } 
  return store;
}

void explore_stack(vector<bool> &visited, vector<vector<int> > &adj,const int &v, stack<int> &store){

  visited[v] = true;	

  for (auto w : adj[v])
  {
    if(visited[w]) continue;
    explore_stack(visited,adj,w,store);      
  }
	store.push(v);
}


int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x].push_back(y);
  }
  SCC(adj);
}       