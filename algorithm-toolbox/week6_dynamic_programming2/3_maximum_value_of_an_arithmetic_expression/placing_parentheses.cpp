#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <tuple>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

long long eval(long long a, long long b, char op) {
    if (op == '*') {
	return a * b;
    } else if (op == '+') {
	return a + b;
    } else if (op == '-') {
	return a - b;
    } else { 
	assert(0);
    }
}


tuple<long long, long long> minmax(int i, int j, const vector<vector<long long>> &M, const vector<vector<long long>> &m, const vector<char> &op){
    long long max_value = LLONG_MIN;
    long long min_value = LLONG_MAX;

    long long a,b,c,d;
    for (int k = i; k <= j-1 ; k++) {
	a = eval(M[i][k],M[k+1][j],op[k]);
	b = eval(M[i][k],m[k+1][j],op[k]);
	c = eval(m[i][k],M[k+1][j],op[k]);
	d = eval(m[i][k],m[k+1][j],op[k]);

	min_value = min(min(min_value, a),min(b,min(c, d)));
	max_value = max(max(max_value, a),max(b,max(c, d)));
    }

    return make_tuple(min_value, max_value);
}

long long get_maximum_value(const string &exp) {

    int n = (exp.length() - 1)/2 + 1;
    
    vector<vector<long long>> m (n+1, vector<long long>(n+1, 0));
    vector<vector<long long>> M (n+1, vector<long long>(n+1, 0));
    vector<char> op (n, 'a');

    string dig;
    for(size_t i = 0, j = 1; i < exp.size(); i++){

	if(i % 2 == 0){	    
	    dig = exp[i];
	    m[j][j] = stoi(dig);
	    M[j][j] = stoi(dig);
	}else{
	    op[j] = exp[i];
	    j++;
	}	
    }
    
    int j = 0;
    for(int s = 1; s <= n-1; s++){
	for (int i = 1; i <= n-s; i++) {
	    j = i + s;
	    tie(m[i][j], M[i][j]) = minmax(i, j, M, m, op);
	}

    }
    
    return M[1][n];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
