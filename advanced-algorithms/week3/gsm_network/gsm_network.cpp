#include <ios>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> int_matrix;

vector<vector<int>> create_index_table(int num_vertices);

struct Edge {
	int from;
	int to;
};
struct ConvertGSMNetworkProblemToSat {
	int numVertices;
	vector<Edge> edges;

	ConvertGSMNetworkProblemToSat(int n, int m) :
		numVertices(n),
		edges(m)
	{  }

	void printEquisatisfiableSatFormula() {

		int_matrix clauses;

		int_matrix translation_table = create_index_table(numVertices);


		
	}
};

int_matrix create_index_table(int num_vertices){

	vector<int> row (3,0);
	int_matrix table (num_vertices,row);

	for (int i = 0, num_variable = 1; i < num_vertices; i++)
	{
		for(int j = 0; j < 3; j++){
			table[i][j] = num_variable;
			num_variable++;			
		}
	}
	
}

int main() {
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	ConvertGSMNetworkProblemToSat converter(n, m);
	for (int i = 0; i < m; ++i) {
		cin >> converter.edges[i].from >> converter.edges[i].to;
	}

	converter.printEquisatisfiableSatFormula();

	return 0;
}
