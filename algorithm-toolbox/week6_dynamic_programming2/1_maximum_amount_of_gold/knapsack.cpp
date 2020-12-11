#include <iostream>
#include <vector>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
  
    int n = w.size();
    vector<int> v = w;
    vector<vector<int>> value(n+1, vector<int>( W+1, 0));
 
    for (int j = 0; j <= W; j++)
      value[0][j] = 0;
 
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
	{
            if (w[i-1] > j)
	      value[i][j] = value[i-1][j];
            else
	      value[i][j] = max(value[i-1][j],
                            value[i-1][j-w[i-1]] + v[i-1]);
	}
    }
 

    return value[n][W];
    
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
	std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}
