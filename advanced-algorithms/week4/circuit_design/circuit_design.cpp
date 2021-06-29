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
stack<int> dfs_stack(vector<vector<int> > &adj);
void explore_stack(vector<bool> &visited, vector<vector<int> > &adj,const int &v, stack<int> &store);
int variable_to_vertex(int variable, int numVars);
vector<vector<int>> reverse_graph(vector<vector<int>> &implication_graph);
void explore_scc(vector<bool> &visited, vector<vector<int> > &reversed, int &v, unordered_set<int> &scc);
vector<unordered_set<int>> dfs_scc(vector<vector<int>> &reverserd, stack<int> store);
vector<unordered_set<int>> SCC(vector<vector<int>> &implication_graph);
bool is_unsatisfiable(vector<unordered_set<int>> &sccs, int numVars);
int vertex_to_variable(int vertex, int numVars);
vector<int> find_result(vector<unordered_set<int>> &sccs, int numVars);

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
				vector<unordered_set<int>> sccs = SCC(implication_graph);

				if(is_unsatisfiable(sccs,numVars)) return false;

				result = find_result(sccs, numVars);
				return true;
    }
};

void set_result(int variable, vector<int> &result){

	bool already_set = result[abs(variable)-1] != -1;
	if(already_set) return;

	if(variable < 0){
		result[abs(variable)-1] = 0;
	}else{
		result[variable -1] = 1;
	}
}

vector<int> find_result(vector<unordered_set<int>> &sccs, int numVars){
	vector<int> result(numVars, -1);
	
	for(unordered_set<int> scc : sccs){
		for(int vertex : scc){
			int variable = vertex_to_variable(vertex,numVars);
			set_result(variable, result);
		}
	}
	return result;
}



bool is_unsatisfiable(vector<unordered_set<int>> &sccs, int numVars){

	for (int var = 1; var <= numVars; var++)
	{
		int x = variable_to_vertex(var, numVars);
		int not_x = variable_to_vertex(-var, numVars);

		for(unordered_set<int> scc : sccs){
			bool x_in_set = scc.find(x) != scc.end();
			bool not_x_in_set = scc.find(not_x) != scc.end();
			if(x_in_set && not_x_in_set) return true;
		}
	}
	return false;
}

vector<unordered_set<int>> SCC(vector<vector<int>> &implication_graph){
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

vector<vector<int>> reverse_graph(vector<vector<int>> &implication_graph){
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

int vertex_to_variable(int vertex, int numVars){

		if(vertex + 1 > numVars)	return (-1)*(vertex + 1 - numVars);
		return vertex + 1;      
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
