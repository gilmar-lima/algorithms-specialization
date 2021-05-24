#include <cmath>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const double EPS = 1e-6;
const int INF = INT_MAX; // it doesn't actually have to be infinity or a big number

const int PRECISION = 6;

typedef std::vector<double> Column;
typedef std::vector<double> Row;
typedef std::vector<Row> Matrix;

int gauss (Matrix a, Column & ans) {
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

Matrix ReadEquation() {
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size + 1, 0.0));
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size + 1; ++column)
            std::cin >> a[row][column];
    }
    return a;
}


Column SolveEquation(Matrix a) {
    
    Column b(a.size(),0.0);
    if(a.size() == 0) return b;

    int solution =  gauss (a, b); 
       
    return b;
}

void PrintColumn(const Column &column) {
    int size = column.size();
    std::cout.precision(PRECISION);
    for (int row = 0; row < size; ++row)
        std::cout << column[row] << std::endl;
}

int main() {
    Matrix equation = ReadEquation();
    Column solution = SolveEquation(equation);
    PrintColumn(solution);
    return 0;
}