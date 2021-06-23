#include <bits/stdc++.h>
#include <stdlib.h>
#include <vector>

using namespace std;


struct Clause {
    int firstVar;
    int secondVar;
};

vector<vector<int>> make_implication_graph(vector<Clause> clauses, int numVars);


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

int variable_to_vertex(int variable, int numVars){

    if(variable<0) return (abs(variable) - 1 + numVars);
    return variable -1;    
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
