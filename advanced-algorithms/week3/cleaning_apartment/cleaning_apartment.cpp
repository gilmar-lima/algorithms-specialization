#include <bits/stdc++.h>
#include <ios>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef vector<vector<int>> int_matrix;

struct Edge {
    int from;
    int to;
};

int_matrix create_index_table(int num_vertices);
int_matrix create_appear_clauses(const int_matrix variables_table);
int_matrix create_every_position_clauses(const int_matrix variables_table);
struct ConvertHampathToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {

        int_matrix variables_table = create_index_table(numVertices);
        

    }
};

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
			for (size_t k = i+1; k < variables_table.size(); k++)
			{
				clauses.push_back({-variables_table[i][j],-variables_table[k][j]});
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
