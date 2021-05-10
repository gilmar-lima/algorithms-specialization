#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

/*
The main method is in this program itself.
Instructions for compiling=>>
Run on any gcc compiler=>>
Special***** should compile in -std=c++11 or C++14 -std=gnu++11  *********  (mat
be other versions syntacs can be different) turorials point online compiler
==> go ti link   http://cpp.sh/ or
https://www.tutorialspoint.com/cplusplus/index.htm and click try it(scorel
below) and after go to c++ editor copy code and paste. after that click button
execute. if you have -std=c++11 you can run in command line; g++ -o output
Simplex.cpp
./output
How to give inputs to the program =>>>
   Example:
        colSizeA = 6 // input colmn size
        rowSizeA = 3  // input row size
    float C[N]={-6,-5,-4,0,0,0};  //Initialize the C array  with the
coefficients of the constraints of the objective function float
B[M]={240,360,300};//Initialize the B array constants of the constraints
respectively
   //initialize the A array by giving all the coefficients of all the variables
   float A[M][N] =  {
                 { 2,  1,  1,   1,  0, 0},
                { 1,  3,  2,   0,  1, 0 },
                {   2,    1,  2,   0,  0,  1}
                };
*/

class Simplex {
 private:
  int rows, cols;
  // stores coefficients of all the variables
  std::vector<std::vector<float> > A;
  // stores constants of constraints
  std::vector<float> B;
  // stores the coefficients of the objective function
  std::vector<float> C;

  float maximum;
  bool isUnbounded;
	int n, m;

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
    // check whether the table is optimal,if optimal no need to process further
    if (checkOptimality() == true) {
      return true;
    }

    // find the column which has the pivot.The least coefficient of the
    // objective function(C array).
    int pivotColumn = findPivotColumn();

    // find the row with the pivot value.The least value item's row in the B
    // array
    int pivotRow = findPivotRow(pivotColumn);

		if (isUnbounded == true) {
      return true;
    }

    // form the next table according to the pivot value
    doPivotting(pivotRow, pivotColumn);

    return false;
  }

  bool checkOptimality() {
    // if the table has further negative constraints,then it is not optimal
    bool isOptimal = false;
    int positveValueCount = 0;

    // check if the coefficients of the objective function are negative
    for (int i = 0; i < C.size(); i++) {
      float value = C[i];
      if (value >= 0) {
        positveValueCount++;
      }
    }
    // if all the constraints are positive now,the table is optimal
    if (positveValueCount == C.size()) {
      isOptimal = true;
      //print();
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
          // C[p] = C[p] - (multiplyValue*C[pivotRow]);
          // B[i] = B[i] - (multiplyValue*B[pivotRow]);
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

  // print the current A array
  /*void print(){
      for(int i=0; i<rows;i++){
          for(int j=0;j<cols;j++){
              cout<<A[i][j] <<" ";
          }
          cout<<""<<endl;
      }
      cout<<""<<endl;
  }*/

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
    float minimum = 99999999;
    int location = 0;
    for (int i = 0; i < sizeof(result) / sizeof(result[0]); i++) {
      if (result[i] > 0) {
        if (result[i] < minimum) {
          minimum = result[i];

          location = i;
        }
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

		 

		if(isUnbounded){
			cout << "Infinity\n";
		}else{
			double sum_solutions = accumulate(C.begin(), C.end(),0);

			if(sum_solutions <= 1.0e9){
				printf("Bounded solution\n");
      	for (float result : C) printf("%.18f ", result);
				cout << "\n";
			}else{
				cout << "Infinity\n";
			}			
      
		}
		
  }
};

void augment_A( vector<vector<float> > &A){
	for (int i = 0, j = A.size(); i < A.size(); i++, j++){
		A[i][j] = 1;    
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

	augment_A(A);

  vector<float> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  vector<float> c(m + n, 0);
  for (int i = 0; i < m; i++) {
		float input;
		cin >> input; 
    c[i] = input*(-1);
  }

  // hear the make the class parameters with A[m][n] vector b[] vector and c[]
  // vector
  Simplex simplex(A, b, c);
  simplex.CalculateSimplex();

  return 0;
}