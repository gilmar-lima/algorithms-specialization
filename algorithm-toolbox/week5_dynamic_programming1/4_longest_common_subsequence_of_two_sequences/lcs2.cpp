#include <iostream>
#include <vector>

using namespace std;

int lcs2(vector<int> &a, vector<int> &b)
{
    int m = a.size(), n = b.size();
 
    int T[m + 1][n + 1];
     
    for (int i = 0; i <= m; i++)
        T[i][0] = 0;
 
    for (int j = 0; j <= n; j++)
        T[0][j] = 0;
 
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
	    if (a[i - 1] == b[j - 1])
                T[i][j] = T[i - 1][j - 1] + 1;
             
            else
                T[i][j] = max(T[i - 1][j], T[i][j - 1]);
        }
    }
  
    return T[m][n];
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < n; i++) {
	std::cin >> a[i];
    }

    size_t m;
    std::cin >> m;
    vector<int> b(m);
    for (size_t i = 0; i < m; i++) {
	std::cin >> b[i];
    }

    cout << lcs2(a,b) << endl;
}
