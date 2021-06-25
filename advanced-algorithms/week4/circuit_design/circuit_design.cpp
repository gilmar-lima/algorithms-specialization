#include <bits/stdc++.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;


struct Clause {
    int firstVar;
    int secondVar;
};

vector<vector<int>> make_implication_graph(vector<Clause> clauses, int numVars);
stack<int> DFS(vector<vector<int> > &adj);
void explore(vector<bool> &visited, vector<vector<int> > &adj,const int &v, stack<int> &store);
int variable_to_vertex(int variable, int numVars);
vector<vector<int>> reverse_graph(vector<vector<int>> implication_graph);

struct TwoSatisfiability {
    int numVars;
    vector<Clause> clauses;

    TwoSatisfiability(int n, int m) :
        numVars(n),
        clauses(m)
    {  }

    bool isSatisfiable(vector<int>& result) {

        vector<vector<int>> implication_graph;
        implication_graph = make_implication_graph(clauses, numVars);
    }
};

vector<unordered_set<int>> SCC(vector<vector<int>> implication_graph){
	stack<int> store = DFS(implication_graph);
	vector<vector<int>> reversed = reverse_graph(implication_graph);

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

stack<int> DFS(vector<vector<int> > &adj){
  stack<int> store;
  vector<bool> visited (adj.size(), false);

  for (size_t v = 0; v < adj.size(); v++)
  {
    if(visited[v]) continue;
    explore(visited,adj,v, store); 
  } 
  return store;
}

void explore(vector<bool> &visited, vector<vector<int> > &adj,const int &v, stack<int> &store){

  visited[v] = true;

  for (auto w : adj[v])
  {
    if(!visited[w]){
      explore(visited,adj,w,store);      
    }else{
      store.push(w);
			return;
    }
  }
}

vector<vector<int>> make_implication_graph(vector<Clause> clauses, int numVars){
    vector<vector<int>> implication_graph (2*numVars);

    for(Clause clause_ : clauses){

        int l1 = variable_to_vertex(clause_.firstVar,numVars);
        int l2 = variable_to_vertex(clause_.secondVar,numVars);
        int not_l1 = variable_to_vertex(-clause_.firstVar,numVars);
        int not_l2 = variable_to_vertex(-clause_.secondVar,numVars);

        implication_graph[not_l1].push_back(l2);
        implication_graph[not_l2].push_back(l1);
    }
    return implication_graph;
}

int variable_to_vertex(int variable, int numVars){

    if(variable<0) return (abs(variable) - 1 + numVars);
    return variable -1;    
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
    }

    vector<int> result(n);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
