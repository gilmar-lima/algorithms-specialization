#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

typedef vector<vector<double>> matrix;

const double EPS = 1e-6;
const int INF = -1;

void augment_A( matrix &A);
void augment_b(vector<double> &b, int num_variables);
int gauss (matrix a, vector<double> & ans);
vector< vector<int> > get_ineq_subsets(int num_inequalites, int num_variables);
matrix subset_matrix(matrix A, vector<int> set);
vector<double> subset_vector(vector<double> b, vector<int> set);

pair<int, vector<double>> solve_diet_problem(
    int n, 
    int m, 
    matrix A, 
    vector<double> b, 
    vector<double> c) {

  augment_A(A);
  augment_b(b,m);

  for(auto subset : get_ineq_subsets(n+m,m)){
    matrix A_subsetted = subset_matrix(A,subset);
    vector<double> b_subsetted = subset_vector(b,subset);


  }
  
  return {0, vector<double>(m, 0)};
}

matrix subset_matrix(matrix A, vector<int> set){
  matrix filtered_matrix;

  for(auto element : set) filtered_matrix.push_back(A[element]);
  return filtered_matrix;
}

vector<double> subset_vector(vector<double> b, vector<int> set){
  vector<double> filtered_vector;

  for(auto element : set) filtered_vector.push_back(b[element]);
  return filtered_vector;
}

void augment_A( matrix &A){

  int num_variables = A[0].size();
	for (int i = 0; i < num_variables; i++){
    vector<double> zero_ineq(num_variables,0);
    zero_ineq[i] = 1;
		A.push_back(zero_ineq);    
	}
}

void augment_b(vector<double> &b, int num_variables){
  int num_ineq = b.size();

	for (int i = num_ineq; i < num_variables+num_ineq; i++){
		b.push_back(0);    
	}
}

int gauss (matrix a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

vector< vector<int> > get_all_subsets(vector<int> set){
    vector< vector<int> > subset;
    vector<int> empty;
    subset.push_back( empty );

    for (int i = 0; i < set.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;  //making a copy of given 2-d vector.

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( set[i] );   // adding set[i] element to each subset of subsetTemp. like adding {2}(in 2nd iteration  to {{},{1}} which gives {{2},{1,2}}.

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );  //now adding modified subsetTemp to original subset (before{{},{1}} , after{{},{1},{2},{1,2}}) 
    }
    return subset;
}

vector< vector<int> > get_ineq_subsets(int num_inequalites, int num_variables){
  auto make_indexes = [num_inequalites](){
    vector<int> indexes(num_inequalites);
    for (size_t i = 0; i < num_inequalites; i++) indexes[i]=i;
    return indexes;    
  };

  auto filter_set_size = [](vector< vector<int> > set, int sets_size){
    vector< vector<int> > filtered_set;
    for(auto element : set){
      if(element.size() == sets_size) filtered_set.push_back(element);
    }
    return filtered_set;
  };

  vector< vector<int> > set_inequalities(get_all_subsets(make_indexes()));

  return filter_set_size(set_inequalities,num_variables);

}
int main(){
  int n, m;
  cin >> n >> m;
  matrix A(n, vector<double>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> A[i][j];
    }
  }
  vector<double> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<double> c(m);
  for (int i = 0; i < m; i++) {
    cin >> c[i];
  }

  pair<int, vector<double>> ans = solve_diet_problem(n, m, A, b, c);

  switch (ans.first) {
    case -1: 
      printf("No solution\n");
      break;
    case 0: 
      printf("Bounded solution\n");
      for (int i = 0; i < m; i++) {
        printf("%.18f%c", ans.second[i], " \n"[i + 1 == m]);
      }
      break;
    case 1:
      printf("Infinity\n");
      break;      
  }
  return 0;
}
