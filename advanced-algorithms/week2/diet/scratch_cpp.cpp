#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
#include <cfloat>
#include <math.h>
using namespace std;
class Simplex {
 private:
  int rows, cols;
  // stores coefficients of all the variables
  vector<std::vector<float> > A;
  // stores constants of constraints
  vector<float> B;
  // stores the coefficients of the objective function
  vector<float> C;

  float maximum;
  bool isUnbounded;
	int n, m;

  vector<float> get_results(){

    vector<float> result;

    for (int i = 0; i < A[0].size(); i++) {  // every basic column has the values, get it form B array
      int count0 = 0;
      int index = 0;
      for (int j = 0; j < rows; j++) {
        if (A[j][i] == 0.0) {
          count0 += 1;
        } else if (A[j][i] == 1) {
          index = j;
        }
      }

      if (count0 == rows - 1) {
        result.push_back(B[index]); 
      } else {
        result.push_back(0); 
      }
    }

    return result;
  }

 public:
  Simplex(std::vector<std::vector<float> > matrix, std::vector<float> b,
          std::vector<float> c) {
    maximum = 0;
    isUnbounded = false;
    rows = matrix.size();
		n = rows;
    cols = matrix[0].size();
		m = cols;
    A.resize(rows, vector<float>(cols, 0));
    B.resize(b.size());
    C.resize(c.size());

    for (int i = 0; i < rows; i++) {  // pass A[][] values to the metrix
      for (int j = 0; j < cols; j++) {
        A[i][j] = matrix[i][j];
      }
    }

    for (int i = 0; i < c.size(); i++) {  // pass c[] values to the B vector
      C[i] = c[i];
    }
    for (int i = 0; i < b.size(); i++) {  // pass b[] values to the B vector
      B[i] = b[i];
    }
  }

  bool simplexAlgorithmCalculataion() {

    if (checkOptimality()) return true;
    
    int pivotColumn = findPivotColumn();

    int pivotRow = findPivotRow(pivotColumn);

		if (isUnbounded == true) {
      return true;
    }

    doPivotting(pivotRow, pivotColumn);

    return false;
  }

  bool checkOptimality() {

    bool isOptimal = false;
    int positveValueCount = 0;

    for (int i = 0; i < C.size(); i++) {
      float value = C[i];
      if (value >= 0) {
        positveValueCount++;
      }
    }

    if (positveValueCount == C.size()) {
      isOptimal = true;
    }
    return isOptimal;
  }

  void doPivotting(int pivotRow, int pivotColumn) {
    float pivetValue = A[pivotRow][pivotColumn];  // gets the pivot value
    float pivotRowVals[cols];                     // the column with the pivot
    float pivotColVals[rows];                     // the row with the pivot
    float rowNew[cols];  // the row after processing the pivot value

    maximum =
        maximum - (C[pivotColumn] *
                   (B[pivotRow] / pivetValue));  // set the maximum step by step
    // get the row that has the pivot value
    for (int i = 0; i < cols; i++) {
      pivotRowVals[i] = A[pivotRow][i];
    }
    // get the column that has the pivot value
    for (int j = 0; j < rows; j++) {
      pivotColVals[j] = A[j][pivotColumn];
    }

    // set the row values that has the pivot value divided by the pivot value
    // and put into new row
    for (int k = 0; k < cols; k++) {
      rowNew[k] = pivotRowVals[k] / pivetValue;
    }

    B[pivotRow] = B[pivotRow] / pivetValue;

    // process the other coefficients in the A array by subtracting
    for (int m = 0; m < rows; m++) {
      // ignore the pivot row as we already calculated that
      if (m != pivotRow) {
        for (int p = 0; p < cols; p++) {
          float multiplyValue = pivotColVals[m];
          A[m][p] = A[m][p] - (multiplyValue * rowNew[p]);
        }
      }
    }

    // process the values of the B array
    for (int i = 0; i < B.size(); i++) {
      if (i != pivotRow) {
        float multiplyValue = pivotColVals[i];
        B[i] = B[i] - (multiplyValue * B[pivotRow]);
      }
    }
    // the least coefficient of the constraints of the objective function
    float multiplyValue = C[pivotColumn];
    // process the C array
    for (int i = 0; i < C.size(); i++) {
      C[i] = C[i] - (multiplyValue * rowNew[i]);
    }

    // replacing the pivot row in the new calculated A array
    for (int i = 0; i < cols; i++) {
      A[pivotRow][i] = rowNew[i];
    }
  }
  // find the least coefficients of constraints in the objective function's
  // position
  int findPivotColumn() {
    int location = 0;
    float minm = C[0];

    for (int i = 1; i < C.size(); i++) {
      if (C[i] < minm) {
        minm = C[i];
        location = i;
      }
    }

    return location;
  }

  // find the row with the pivot value.The least value item's row in the B array
  int findPivotRow(int pivotColumn) {
    float positiveValues[rows];
    std::vector<float> result(rows, 0);
    // float result[rows];
    int negativeValueCount = 0;

    for (int i = 0; i < rows; i++) {
      if (A[i][pivotColumn] > 0) {
        positiveValues[i] = A[i][pivotColumn];
      } else {
        positiveValues[i] = 0;
        negativeValueCount += 1;
      }
    }
    // checking the unbound condition if all the values are negative ones
    if (negativeValueCount == rows) {
      isUnbounded = true;
    } else {
      for (int i = 0; i < rows; i++) {
        float value = positiveValues[i];
        if (value > 0) {
          result[i] = B[i] / value;

        } else {
          result[i] = 0;
        }
      }
    }
    // find the minimum's location of the smallest item of the B array
    float minimum = FLT_MAX;
    int location = 0;
    for (int i = 0; i < B.size(); i++) {
      if (result[i] > 0 && result[i] < minimum) {
        minimum = result[i];
        location = i;
      }
    }

    return location;
  }

  void CalculateSimplex() {
    bool end = false;

    while (!end) {
      bool result = simplexAlgorithmCalculataion();
      if (result == true) end = true;
    }

    vector<float> results = get_results();		 

		if(isUnbounded){
			cout << "Infinity\n";
		}else{
			double sum_solutions = accumulate(results.begin(), results.end(),0);

			if(round(maximum) != 1.0){
				cout << "Bounded solution\n";
      	for (int i = 0; i<(m - n); i++) printf("%.18f ", results[i]);
				cout << "\n";
			}else{
				cout << "No solution\n";
			}			
      
		}
		
  }
};

void augment_A( vector<vector<float> > &A, int num_variables){
	for (int i = 0, j = num_variables; i < A.size(); i++, j++){
		A[i][j] = 1;    
	}
}

void invert_line( vector<vector<float> > &A, int line){

  for (int j = 0; j < A[0].size(); j++){
		A[line][j] = -1*A[line][j];    
	}
}

int main() {
  int n, m;
  cin >> n >> m;
  std::vector<std::vector<float> > A(n, vector<float>(m + n,0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { 
      cin >> A[i][j];
    }
  }

	augment_A(A,m);

  vector<float> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    if(b[i]<0){
      b[i] = -b[i];
      invert_line(A,i);
    }
  }

  vector<float> c(m + n, 0);
  for (int i = 0; i < m; i++) {
		float input;
		cin >> input; 
    c[i] = input*(-1);
  }

  Simplex simplex(A, b, c);
  simplex.CalculateSimplex();

  return 0;
}