#include <bits/stdc++.h>
#include <ios>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>

using namespace std;

typedef vector<vector<int>> int_matrix;

struct Edge {
    int from;
    int to;
};

int_matrix create_index_table(int num_vertices);
int_matrix create_appear_clauses(const int_matrix variables_table);
int_matrix create_every_position_clauses(const int_matrix variables_table);
int_matrix create_two_nodes_clauses(const int_matrix variables_table);
int_matrix create_appear_twice_clauses(const int_matrix variables_table);
unordered_set<string> pairs_in_graph(vector<Edge> edges);
int_matrix create_nonadjacent_nodes_clauses(const int_matrix variables_table, vector<Edge> edges);
void print_clauses(int_matrix clauses, int num_vertices);
void print_clauses_file(int_matrix clauses, int num_vertices);
struct ConvertHampathToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {

      int_matrix variables_table = create_index_table(numVertices);
			int_matrix two_nodes_clauses = create_two_nodes_clauses(variables_table);
			int_matrix every_position_clauses = create_every_position_clauses(variables_table);
			int_matrix appear_clauses = create_appear_clauses(variables_table);
			int_matrix appear_twice_clauses = create_appear_twice_clauses(variables_table);
			int_matrix nonadjacent_nodes_clauses = create_nonadjacent_nodes_clauses(variables_table, edges);

			int_matrix clauses;

			clauses.insert(clauses.end(),appear_clauses.begin(), appear_clauses.end());
			clauses.insert(clauses.end(),appear_twice_clauses.begin(), appear_twice_clauses.end());  
			clauses.insert(clauses.end(),every_position_clauses.begin(), every_position_clauses.end());
			clauses.insert(clauses.end(),two_nodes_clauses.begin(), two_nodes_clauses.end());
			clauses.insert(clauses.end(),nonadjacent_nodes_clauses.begin(), nonadjacent_nodes_clauses.end());

			print_clauses(clauses, numVertices);
			//print_clauses_file(clauses, numVertices);
		}
};

void print_clauses_file(int_matrix clauses, int num_vertices){

	int num_variables = num_vertices*num_vertices;	
	ofstream file;
	file.open("clauses_cleaning_apartment.cnf");

	file << "p cnf ";
	file << num_variables;
	file <<" "<< clauses.size() << endl;

	for(auto clause : clauses){
		for(auto variable : clause){
			file << variable << ' ';
		}
		file << "0" << endl;
	}
	file.close();
}

void print_clauses(int_matrix clauses, int num_vertices){

	int num_variables = num_vertices*num_vertices;
	cout << clauses.size() << " ";
	cout << num_variables << endl;

	for(auto clause : clauses){
		for(auto variable : clause){
			cout << variable << " ";
		}
		cout << "0" << endl;
	}
}

int_matrix create_appear_clauses(const int_matrix variables_table){

	int_matrix clauses;
	vector<int> clause (variables_table.size(),0);
	
	for (size_t j = 0; j < variables_table[0].size(); j++)
	{
		for (size_t i = 0; i < variables_table.size(); i++)
		{
			clause[i] = variables_table[i][j];
		}
		clauses.push_back(clause);		
	}
	return clauses;
}

int_matrix create_appear_twice_clauses(const int_matrix variables_table){

	int_matrix clauses;	
	
	for (size_t j = 0; j < variables_table[0].size(); j++)
	{
		for (size_t i = 0; i < variables_table.size(); i++)
		{
			for (size_t k = 0; k < variables_table.size(); k++)
			{
				if(i>=k) continue;
				clauses.push_back({-variables_table[i][j],-variables_table[k][j]});
			}			
		}
	}
	return clauses;
}

int_matrix create_every_position_clauses(const int_matrix variables_table){

	int_matrix clauses;
	vector<int> clause (variables_table[0].size(),0);
	
	for (size_t i = 0; i < variables_table.size(); i++)
	{
		for (size_t j = 0; j < variables_table[0].size(); j++)
		{
			clause[j] = variables_table[i][j];
		}
		clauses.push_back(clause);		
	}
	return clauses;
}

int_matrix create_two_nodes_clauses(const int_matrix variables_table){

	int_matrix clauses;	
	
	for (size_t i = 0; i < variables_table.size(); i++)
	{
		for (size_t j = 0; j < variables_table[0].size(); j++)
		{
			for (size_t k = 0; k < variables_table[0].size(); k++)
			{
				if(j>=k) continue;
				clauses.push_back({-variables_table[i][j],-variables_table[i][k]});
			}			
		}
	}
	return clauses;
}

int_matrix create_nonadjacent_nodes_clauses(const int_matrix variables_table, vector<Edge> edges){

	unordered_set<string> graph_pairs = pairs_in_graph(edges);
	unordered_set<string>::const_iterator set_iterator;

	int_matrix clauses;	
	
	for (size_t j = 0; j < variables_table.size(); j++)
	{
		for (size_t i = 0; i < variables_table.size(); i++)
		{
			if(i==j) continue;

			set_iterator = graph_pairs.find(to_string(i+1)+'-'+to_string(j+1));
			bool pair_in_graph = set_iterator != graph_pairs.end();
			if(pair_in_graph) continue;	

			for (size_t k = 0; k < variables_table.size() - 1; k++)
			{								
				clauses.push_back({-variables_table[k][i],-variables_table[k+1][j]});
			}			
		}
	}
	return clauses;
}

int_matrix create_index_table(int num_vertices){
	
	vector<int> row (num_vertices,0);
	int_matrix table (num_vertices,row);

	for (int i = 0, num_variable = 1; i < num_vertices; i++)
	{
		for(int j = 0; j < num_vertices; j++){
			table[i][j] = num_variable;
			num_variable++;			
		}
	}
	return table;	
}

unordered_set<string> pairs_in_graph(vector<Edge> edges){

	unordered_set<string> pairs_in_graph;

	for(Edge edge_ : edges){
		pairs_in_graph.insert(to_string(edge_.from)+'-'+to_string(edge_.to));
		pairs_in_graph.insert(to_string(edge_.to)+'-'+to_string(edge_.from));
	}
	return pairs_in_graph;
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
