#include <ios>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> int_matrix;

const int NUM_COLORS = 3;
struct Edge {
	int from;
	int to;
};

vector<vector<int>> create_index_table(int num_vertices);
int_matrix create_relation_clauses(vector<Edge> edges, int_matrix table);
int_matrix create_color_clauses(int num_vertices, int_matrix table);
void print_clauses(int_matrix clauses);
struct ConvertGSMNetworkProblemToSat {
	int numVertices;
	vector<Edge> edges;

	ConvertGSMNetworkProblemToSat(int n, int m) :
		numVertices(n),
		edges(m)
	{  }

	void printEquisatisfiableSatFormula() {

		int_matrix relation_clauses, color_clauses;
		int_matrix clauses;

		int_matrix translation_table = create_index_table(numVertices);
		relation_clauses = create_relation_clauses(edges, translation_table);
		color_clauses = create_color_clauses(numVertices, translation_table);

		clauses.insert(clauses.begin(),relation_clauses.begin(), relation_clauses.end());
		clauses.insert(clauses.end(), color_clauses.begin(), color_clauses.end());

		print_clauses(clauses);
	}
};

void print_clauses(int_matrix clauses){

	for(auto clause : clauses){
		for(auto variable : clause){
			cout << variable << ' ';
		}
		cout << endl;
	}
}

int_matrix create_color_clauses(int num_vertices, int_matrix table){

	int_matrix clauses;
	for (size_t vertex = 1; vertex <= num_vertices; vertex++)
	{
		clauses.push_back({table[vertex-1][0], -table[vertex-1][1], -table[vertex-1][2]});
		clauses.push_back({-table[vertex-1][0], table[vertex-1][1], -table[vertex-1][2]});
		clauses.push_back({-table[vertex-1][0], -table[vertex-1][1], table[vertex-1][2]});
	}
	return clauses;
}

int_matrix create_relation_clauses(vector<Edge> edges, int_matrix table){

	int_matrix clauses;

	for(Edge e : edges){
		for (size_t color = 1; color <= NUM_COLORS; color++)
		{
			clauses.push_back({table[e.from-1][color-1], table[e.to-1][color-1]});
			clauses.push_back({-table[e.from-1][color-1], -table[e.to-1][color-1]});			
		}
	}
	return clauses;
}

int_matrix create_index_table(int num_vertices){

	vector<int> row (NUM_COLORS,0);
	int_matrix table (num_vertices,row);

	for (int i = 0, num_variable = 1; i < num_vertices; i++)
	{
		for(int j = 0; j < NUM_COLORS; j++){
			table[i][j] = num_variable;
			num_variable++;			
		}
	}
	return table;
	
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
